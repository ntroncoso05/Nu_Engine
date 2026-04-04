#pragma once
#include "Context.h"

namespace Nu
{
    struct AppInterface
    {
        NU_INLINE virtual ~AppInterface() = default;

        // create entity
        template<typename Entt, typename... Args>
        NU_INLINE Entt CreateEntt(Args&&... args)
        {
            NU_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&m_Context->Scene, std::forward<Args>(args)...));
            glCheckError();
        }

        // convert id to entity
        template<typename Entt>
        NU_INLINE Entt ToEntt(EntityID entity)
        {
            NU_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&m_Context->Scene, entity));
            glCheckError();
        }

        // loop through entities
        template<typename Entt, typename Comp, typename Task>
        NU_INLINE void EnttView(Task&& task)
        {
            NU_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            m_Context->Scene.view<Comp>().each([this, &task](auto entity, auto& comp)
                {
                    task(std::move(Entt(&m_Context->Scene, entity)), comp);
                });
                glCheckError();
        }

        // attach event callback
        template<typename Event, typename Callback>
        NU_INLINE void AttachCallback(Callback&& callback)
        {
            m_Context->Dispatcher.AttachCallback<Event>(std::move(callback), m_LayerID);
            glCheckError();
        }

        // post event
        template<typename Event, typename... Args>
        NU_INLINE void PostEvent(Args&&... args)
        {
            m_Context->Dispatcher.PostEvent<Event>(std::forward<Args>(args)...);
            glCheckError();
        }

        // post task event
        template<typename Task>
        NU_INLINE void PostTask(Task&& task)
        {
            m_Context->Dispatcher.PostTask(std::move(task));
            glCheckError();
        }

        // detach callback
        template<typename Event>
        NU_INLINE void DetachCallback()
        {
            m_Context->Dispatcher.DetachCallback<Event>(m_LayerID);
            glCheckError();
        }

        template<typename Layer, typename... Args>
        NU_INLINE Layer* AttachLayer(Args&&... args)
        {
            // check layer's type compliance
            NU_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);

            // check if layer already exist
            if(GetLayer<Layer>() != nullptr)
            {
                NU_ERROR("Layer already attached!");
                return nullptr;
            }

            // create layer and add to collection
            auto layer = new Layer(std::forward<Args>(args)...);
            m_Context->Layers.push_back(layer);
            layer->m_LayerID = TypeID<Layer>();
            layer->m_Context = m_Context;
            layer->OnStart();
            glCheckError();
            return layer;
        }

        template<typename Layer>
        NU_INLINE void DetachLayer()
        {
            NU_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);
            m_Context->Dispatcher.PostTask([this]
            {
                m_Context->Layers.erase(std::remove_if(m_Context->Layers.begin(),
                    m_Context->Layers.end(), [this](auto& layer)
                    {
                        if(layer->m_LayerID == TypeID<Layer>())
                        {
                            m_Context->Dispatcher.EraseListener(layer->m_LayerID);
                            NU_DELETE(layer);
                            return true;
                        }
                        return false;
                    }),
                m_Context->Layers.end());
            });
            glCheckError();
        }

        template<typename Layer>
        NU_INLINE Layer* GetLayer()
        {
            glCheckError();
            NU_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);
            auto itr = std::find_if(m_Context->Layers.begin(),
                m_Context->Layers.end(), [this] (auto layer)
                {
                    return (layer->m_LayerID == TypeID<Layer>());
                });

            if(itr != m_Context->Layers.end())
            {
                return static_cast<Layer*>(*itr);
            }
            return nullptr;
        }
    protected:
        NU_INLINE virtual void OnUpdate() {}
        NU_INLINE virtual void OnStart() {}
    private:
        friend struct Application;
        AppContext* m_Context;
        uint32_t m_LayerID;
    };
}