#version 330 core
layout (location = 0) in vec3 a_position;

out vec3 world_position;

uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    gl_Position = u_proj * u_view * vec4(a_position, 1.0f);
    world_position = a_position;
}

++VERTEX++

#version 330 core
out vec4 out_fragment;
in vec3 world_position;

#define PI 3.14159265358979323846

uniform samplerCube u_cubemap;

void main()
{
    vec3 N = normalize(world_position);
    vec3 irradiance = vec3(0.0f);

    // irradiance
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 right = cross(up, N);
    up = cross(N, right);

    int nrSamples = 0;
    float sampleDelta = 0.025f;

    for(float phi = 0.0f; phi < 2.0f * PI; phi += sampleDelta)
    {
        for(float theta = 0.0f; theta < 0.5f * PI; theta += sampleDelta)
        {
            // spherical to cartesian (in tangent space)
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));

            // tangent space to world
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;

            // compute irradiance value
            irradiance += texture(u_cubemap, sampleVec).rgb * cos(theta) * sin(theta);

            // increment sample count
            nrSamples++;
        }
    }

    irradiance = PI * irradiance * (1.0f / float(nrSamples));
    out_fragment = vec4(irradiance, 1.0f);
}

++FRAGMENT++