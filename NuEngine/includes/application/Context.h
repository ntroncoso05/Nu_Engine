#pragma once
#include "window/Window.h"

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
        }

        NU_INLINE ~AppContext()
        {
            for(auto& layer : Layers)
            {
                NU_DELETE(layer);
            }
        }

        std::vector<AppInterface*> Layers;
        std::unique_ptr<AppWindow> Window;
        EventDispatcher Dispatcher;
    };
}