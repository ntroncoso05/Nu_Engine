#pragma once
#include "window/Window.h"
#include "physics/Context.h"
#include "graphics/Renderer.h"

namespace Nu
{
    // forward declaration
    struct AppInterface;

    // application context
    struct AppContext
    {
        NU_INLINE AppContext()
        {
            Window = std::make_unique<AppWindow>(&Dispatcher, 1280, 720, "Nu Engine!");
            Renderer = std::make_unique<GraphicsRenderer>(1280, 720);
            Physics = std::make_unique<PhysicsContext>();
            DeltaTime = 0.0f;
            glCheckError();
        }

        NU_INLINE ~AppContext()
        {
            for(auto layer : Layers)
            {
                NU_DELETE(layer);
            }
            glCheckError();
        }

        std::unique_ptr<GraphicsRenderer> Renderer;
        std::unique_ptr<PhysicsContext> Physics;
        std::vector<AppInterface*> Layers;
        std::unique_ptr<AppWindow> Window;
        EventDispatcher Dispatcher;
        EntityRegistry Scene;
        float DeltaTime;
    };
}