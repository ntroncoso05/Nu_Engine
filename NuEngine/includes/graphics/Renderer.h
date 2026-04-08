#pragma once
#include "buffers/Frame.h"
#include "shaders/Final.h"
#include "shaders/PBR.h"

namespace Nu
{
    struct GraphicsRenderer
    {
        NU_INLINE GraphicsRenderer(int32_t width, int32_t height)
        {
            // initialize opengl
            if(glewInit() != GLEW_OK)
            {
                NU_FATAL("Failed to initialize glew!");
                exit(EXIT_FAILURE);
            }
            glewExperimental = GL_TRUE;
            
            m_Final = std::make_unique<FinalShader>("Resources/shaders/final.glsl");
            m_Pbr = std::make_unique<PbrShader>("Resources/shaders/pbr.glsl");            
            m_Frame = std::make_unique<FrameBuffer>(width, height);
            glCheckError();
        }

        NU_INLINE void SetDirectLight(DirectLight& light, Transform3D& transform, uint32_t index) 
        {
            m_Pbr->SetDirectLight(light, transform, index);
        }

        NU_INLINE void SetPointLight(PointLight& light, Transform3D& transform, uint32_t index) 
        {
            m_Pbr->SetPointLight(light, transform, index);
        }

        NU_INLINE void SetSpotLight(SpotLight& light, Transform3D& transform, uint32_t index) 
        {
            m_Pbr->SetSpotLight(light, transform, index);
        }

        // --

        NU_INLINE void SetDirectLightCount(int32_t count)
        {
            m_Pbr->SetDirectLightCount(count);
        }

        NU_INLINE void SetPointLightCount(int32_t count)
        {
            m_Pbr->SetPointLightCount(count);
        }

        NU_INLINE void SetSpotLightCount(int32_t count)
        {
            m_Pbr->SetSpotLightCount(count);
        }
       
        // --

        NU_INLINE void Draw(Model3D& model, PbrMaterial& material, Transform3D& transform)
        {
            m_Pbr->Draw(model, material, transform);
        }

        NU_INLINE void SetCamera(Camera3D& camera, Transform3D& transform)
        {
            m_Pbr->SetCamera(camera, transform, m_Frame->Ratio());
        }

        NU_INLINE void Resize(int32_t width, int32_t height)
        {
            m_Frame->Resize(width, height);
        }

        // --

        NU_INLINE uint32_t GetFrame()
        {
            return m_Frame->GetTexture();
        }

        NU_INLINE void ShowFrame()
        {
            m_Final->Show(m_Frame->GetTexture());
        }

        NU_INLINE void NewFrame()
        {
            m_Frame->Begin();
            m_Pbr->Bind();
        }

        NU_INLINE void EndFrame()
        {
            m_Pbr->Unbind();
            m_Frame->End();
        }
    private:
        std::unique_ptr<FrameBuffer> m_Frame;
        std::unique_ptr<FinalShader> m_Final;
        std::unique_ptr<PbrShader> m_Pbr;
    };
}