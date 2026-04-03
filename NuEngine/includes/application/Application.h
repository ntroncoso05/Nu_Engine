#pragma once
#include "Interface.h"

namespace Nu
{
    struct Application : AppInterface
    {
        NU_INLINE Application()
        {
            m_LayerID = TypeID<Application>();
            m_Context = new AppContext();
        }

        NU_INLINE ~Application()
        {
            NU_DELETE(m_Context);
        }

        NU_INLINE void RunContext()
        {
            while(m_Context->Window->PollEvents()) // Handle events
            {                
                for(auto layer : m_Context->Layers) // updates layers
                {
                    layer->OnUpdate();
                }
            }
        }
    };
}