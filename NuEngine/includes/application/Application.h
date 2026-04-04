#pragma once
#include "Interface.h"

namespace Nu
{
    struct Application : AppInterface
    {
        NU_INLINE Application()
        {
            // initialize application context
            m_LayerID = TypeID<Application>();
            m_Context = new AppContext();

            // attach window resize event callback
            AttachCallback<WindowResizeEvent>([this](auto e)
                {
                    m_Context->Renderer->Resize(e.Width, e.Height);
                });
                glCheckError();
        }

        NU_INLINE ~Application()
        {
            NU_DELETE(m_Context);
        }

        NU_INLINE void RunContext()
        {
            // create scene camera
            auto camera = CreateEntt<Entity>();
            camera.Attach<TransformComponent>().Transform.Translate.z = 2.0f;
            camera.Attach<CameraComponent>();
            
            // create cube entity
            auto model = std::make_shared<Model>("Resources/models/backpack/backpack.obj");
            auto cube = CreateEntt<Entity>();
            cube.Attach<TransformComponent>().Transform.Rotation.y = 30.0f;
            cube.Attach<ModelComponent>().Model = model;

            while(m_Context->Window->PollEvents()) // Handle events
            {
                // render new frame
                m_Context->Renderer->NewFrame();
                {
                    // set shader camera
                    EnttView<Entity, CameraComponent>([this](auto entity, auto& comp)
                        {
                            auto& transform = entity.template Get<TransformComponent>().Transform;
                            m_Context->Renderer->SetCamera(comp.Camera, transform);
                        });

                    // render models
                    EnttView<Entity, ModelComponent>([this](auto entity, auto& comp)
                        {
                            auto& transform = entity.template Get<TransformComponent>().Transform;
                            m_Context->Renderer->Draw(comp.Model, transform);
                        });

                }
                m_Context->Renderer->EndFrame();

                // update layers
                for(auto layer : m_Context->Layers)
                {
                    layer->OnUpdate();
                }                
                glCheckError();
                // show frame to screen
                m_Context->Renderer->ShowFrame();
            }
        }
    };
}