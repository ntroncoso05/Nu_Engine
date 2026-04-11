#pragma once
#include "shaders/Prefiltered.h"
#include "shaders/Irradiance.h"
#include "shaders/Skybox.h"
#include "shaders/SkyMap.h"
#include "shaders/Shadow.h"
#include "Shaders/Bloom.h"
#include "buffers/Frame.h"
#include "shaders/Final.h"
#include "shaders/BRDF.h"
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

            // make the skybox edges look smooth
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

            m_Bloom = std::make_unique<BloomShader>("Resources/shaders/bloom.glsl", width, height);

            // skybox shaders
            m_Prefil = std::make_unique<PrefilteredShader>("Resources/shaders/prefiltered.glsl");
            m_Irrad = std::make_unique<IrradianceShader>("Resources/shaders/irradiance.glsl");
            m_Skybox = std::make_unique<SkyboxShader>("Resources/shaders/skybox.glsl");
            m_SkyMap = std::make_unique<SkyMapShader>("Resources/shaders/skymap.glsl");
            m_Brdf = std::make_unique<BrdfShader>("Resources/shaders/brdf.glsl");
            
           // render shaders
           m_Shadow = std::make_unique<ShadowShader>("Resources/shaders/shadow.glsl");
           m_Final = std::make_unique<FinalShader>("Resources/shaders/final.glsl");
           m_Pbr = std::make_unique<PbrShader>("Resources/shaders/pbr.glsl");
            
            m_Frame = std::make_unique<FrameBuffer>(width, height);
            m_SkyboxMesh = CreateSkyboxMesh();
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
            m_Pbr->Draw(model, material, transform); glCheckError();
        }

        NU_INLINE void SetJoints(std::vector<glm::mat4>& transforms) 
        {
            m_Pbr->SetJoints(transforms);
        }

        NU_INLINE void DrawDepth(Model3D& model, Transform3D& transform)
        {
            m_Shadow->Draw(model, transform);
        }

        // initializes skybox
        NU_INLINE void InitSkybox(Skybox& sky, Texture& texture, int32_t size)
        {
            // generate brdf map
            sky.BrdfMap = m_Brdf->Generate(512);

            // generate enviroment cube map
            sky.CubeMap = m_SkyMap->Generate(texture, m_SkyboxMesh, size);

            // generate diffuse irradiance map
            sky.IrradMap = m_Irrad->Generate(sky.CubeMap, m_SkyboxMesh, 32);

            // generate specular irradiance map
            sky.PrefilMap = m_Prefil->Generate(sky.CubeMap, m_SkyboxMesh, 128);
        }

        // Render skybox
        NU_INLINE void DrawSkybox(Skybox& sky, Transform3D& transform)
        {
            // render skybox
            m_Skybox->Draw(m_SkyboxMesh, sky.CubeMap, transform);

            // set all enviroment map
            m_Pbr->SetEnvMaps(sky.IrradMap, sky.PrefilMap, sky.BrdfMap, m_Shadow->GetDepthMap());
        }

        NU_INLINE void SetCamera(Camera3D& camera, Transform3D& transform)
        {
            float aspect = m_Frame->Ratio();
            m_Pbr->SetCamera(camera, transform, aspect);

            // binds skybox shader and set mvp
            m_Skybox->SetCamera(camera, transform, aspect);

            // rebind pbr shader again
            m_Pbr->Bind();
        }

        NU_INLINE void Resize(int32_t width, int32_t height)
        {
            m_Frame->Resize(width, height);
        }

        // starts the depth rendering process
        NU_INLINE void BeginShadowPass(const glm::vec3& LightDir)
        {            
            // prepare projection and view mtx
            float nearPlane = 1.0f;
            float farPlane = 10.0f;
            static auto proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
            auto view = glm::lookAt(LightDir, glm::vec3(0.0f, 0.0f,  0.0f), glm::vec3(0.0f, 1.0f,  0.0f));

            // compute light space matrix
            auto lightSpaceMtx = (proj * view);

            // set pbr shader light space mtx and depth map
            m_Pbr->Bind();
            m_Pbr->SetLightSpaceMatrix(lightSpaceMtx);

            // begin depth rendering
            m_Shadow->BeginFrame(lightSpaceMtx);   
        }

        // ends the depth rendering process
        NU_INLINE void EndShadowPass()
        {
            m_Shadow->EndFrame();
        }

        // --

        NU_INLINE uint32_t GetFrame()
        {
            return m_Frame->GetTexture();
        }

        NU_INLINE void ShowFrame()
        {
            glViewport(0, 0, m_Frame->Width(), m_Frame->Height());
            m_Final->Show(m_Frame->GetTexture(), m_Bloom->GetMap());
            //m_Final->Show(m_Shadow->GetDepthMap()); //for testing shadows
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

            // post-processing
            m_Bloom->Compute(m_Frame->GetBrightnessMap(), 10);
        }
    private:
        std::unique_ptr<BloomShader> m_Bloom;
        std::unique_ptr<PrefilteredShader> m_Prefil;
        std::unique_ptr<IrradianceShader> m_Irrad;
        std::unique_ptr<SkyboxShader> m_Skybox;
        std::unique_ptr<ShadowShader> m_Shadow;
        std::unique_ptr<SkyMapShader> m_SkyMap;
        std::unique_ptr<FrameBuffer> m_Frame;
        std::unique_ptr<FinalShader> m_Final;
        std::unique_ptr<BrdfShader> m_Brdf;
        std::unique_ptr<PbrShader> m_Pbr;
        SkyboxMesh m_SkyboxMesh;
    };
}