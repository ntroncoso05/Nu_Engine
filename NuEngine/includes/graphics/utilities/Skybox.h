#pragma once
#include "../buffers/Mesh.h"

namespace Nu
{
    // skybox mesh typw definition
    using SkyboxMesh = std::unique_ptr<Mesh<SkyboxVertex>>;

    // helps render a skybox mesh
    NU_INLINE void RenderSkyboxMesh(SkyboxMesh& mesh)
    {
        // Enable back face culling
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Disable writing to the depth buffer
        glDepthMask(GL_FALSE);
        // Set the depth function to LEQUAL (less than or equal)
        glDepthFunc(GL_LEQUAL);

        // Draw the skybox mesh using triangles
        mesh->Draw(GL_TRIANGLES);
        
        // reset the depth fuction to LESS (default)
        glDepthFunc(GL_LESS);
        // enable writing to the depth buffer again
        glDepthMask(GL_TRUE);
        // Disable face culling
        glDisable(GL_CULL_FACE);
        glCheckError();
    }

    // helps create a skybox mesh
    NU_INLINE SkyboxMesh CreateSkyboxMesh()
    {
        // cube vertices
        std::vector<glm::vec3> positions = 
        {
            { -1.0f,  1.0f, -1.0f },
            { -1.0f, -1.0f, -1.0f },
            {  1.0f, -1.0f, -1.0f },
            {  1.0f, -1.0f, -1.0f },
            {  1.0f,  1.0f, -1.0f },
            { -1.0f,  1.0f, -1.0f },

            { -1.0f, -1.0f,  1.0f },
            { -1.0f, -1.0f, -1.0f },
            { -1.0f,  1.0f, -1.0f },
            { -1.0f,  1.0f, -1.0f },
            { -1.0f,  1.0f,  1.0f },
            { -1.0f, -1.0f,  1.0f },
 
            { 1.0f, -1.0f, -1.0f },
            { 1.0f, -1.0f,  1.0f },
            { 1.0f,  1.0f,  1.0f },
            { 1.0f,  1.0f,  1.0f },
            { 1.0f,  1.0f, -1.0f },
            { 1.0f, -1.0f, -1.0f },

            { -1.0f, -1.0f,  1.0f },
            { -1.0f,  1.0f,  1.0F },
            {  1.0f,  1.0f,  1.0f },
            {  1.0f,  1.0f,  1.0f },
            {  1.0f, -1.0f,  1.0f },
            { -1.0f, -1.0f,  1.0f },

            { -1.0f,  1.0f, -1.0f },
            {  1.0f,  1.0f, -1.0f },
            {  1.0f,  1.0f,  1.0f },
            {  1.0f,  1.0f,  1.0f },
            { -1.0f,  1.0f,  1.0f },
            { -1.0f,  1.0f, -1.0f },

            { -1.0f, -1.0f, -1.0f },
            { -1.0f, -1.0f,  1.0f },
            {  1.0f, -1.0f, -1.0f },
            {  1.0f, -1.0f, -1.0f },
            { -1.0f, -1.0f,  1.0f },
            {  1.0f, -1.0f,  1.0f }
        };  

        // set mesh data
        MeshData<SkyboxVertex> data;
        for(uint32_t i = 0; i < positions.size(); ++i)
        {
            data.Vertices.push_back({ positions[i] });
        }      
        // create and return skybox mesh
        return std::make_unique<Mesh<SkyboxVertex>>(data);
    }
}