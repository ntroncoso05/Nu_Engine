#version 330 core
layout (location = 0) in vec4 a_quad;

out vec2 uvs;

void main()
{
    gl_Position = vec4(a_quad.x, a_quad.y, 0.0f, 1.0f);
    uvs = vec2(a_quad.z, a_quad.w);
}

++VERTEX++

#version 330 core
out vec4 out_fragment;
in vec2 uvs;

const float GAMMA = 2.5f;
const float EXPOSURE = 10.0f;
const float MIN_GAMMA = 0.000001f;

uniform sampler2D u_map;
uniform sampler2D u_bloom;

void main()
{
    // combine actual color and the bloom color
    vec3 result = texture(u_map, uvs).rgb + texture(u_bloom, uvs).rgb;

    // sample color from map
    result = pow(result, vec3(GAMMA));

    // process exposure
    result = vec3(1.0f) - exp(-result * EXPOSURE);

    // gamma correction
    result = pow(result, vec3(1.0f / max(GAMMA, MIN_GAMMA)));

    // fragment color
    out_fragment = vec4(result, 1.0f);

    // get depth value optional for testing
    //float depth = texture(u_map,uvs).r;
    // fragment color
    //out_fragment = vec4(depth, depth, depth, depth);
}

++FRAGMENT++