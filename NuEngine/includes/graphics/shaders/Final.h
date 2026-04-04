#pragma once
#include "Shader.h"
#include "../utilities/Quad.h"

namespace Nu
{
    struct FinalShader : Shader
    {
        NU_INLINE FinalShader(const std::string& filename) : Shader(filename)
        {
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

        NU_INLINE void Show(uint32_t map)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(m_ShaderID);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, map);

            glUniform1i(u_Map, 0);
            m_Quad->Draw(GL_TRIANGLES);
            glUseProgram(0);
            glCheckError();
        }
    private:
        uint32_t u_Map = 0u;
        Quad2D m_Quad;
    };
}