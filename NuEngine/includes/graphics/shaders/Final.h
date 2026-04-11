#pragma once
#include "Shader.h"
#include "../utilities/Quad.h"

namespace Nu
{
    struct FinalShader : Shader
    {
        NU_INLINE FinalShader(const std::string& filename) : Shader(filename)
        {
            u_Bloom = glGetUniformLocation(m_ShaderID, "u_bloom");
            u_Map = glGetUniformLocation(m_ShaderID, "u_map");
            m_Quad = CreateQuad2D();
            glCheckError();
        }

        NU_INLINE void SetSceneMap(uint32_t map)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, map);
            glUniform1i(u_Map, 0);
            glCheckError();
        }

        NU_INLINE void Show(uint32_t map, uint32_t bloom)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glUseProgram(m_ShaderID);

            // set color map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, map);
            glUniform1i(u_Map, 0);

            // set bloom map
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, bloom);
            glUniform1i(u_Bloom, 1);

            // render quad
            m_Quad->Draw(GL_TRIANGLES);
            glUseProgram(0);
            glCheckError();
        }
    private:
        uint32_t u_Bloom = 0u;
        uint32_t u_Map = 0u;
        Quad2D m_Quad;
    };
}