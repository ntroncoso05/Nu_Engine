#pragma once
#include <entt/entt.hpp>
#include "graphics/utilities/Data.h"
#include "physics/Utilities.h"

namespace Nu
{
    // typedefs
    using EntityID = entt::entity;
    using EntityRegistry = entt::registry;
    constexpr EntityID NENTT = entt::null; // null entity

    // ++
    
    // direct light component
    struct DirectLightComponent 
    {
        NU_INLINE DirectLightComponent(const DirectLightComponent&) = default;
        NU_INLINE DirectLightComponent() = default; 
        DirectLight Light;
    };

    // point light component
    struct PointLightComponent 
    {
        NU_INLINE PointLightComponent(const PointLightComponent&) = default;
        NU_INLINE PointLightComponent() = default; 
        PointLight Light;
    };

    // point light component
    struct SpotLightComponent 
    {
        NU_INLINE SpotLightComponent(const SpotLightComponent&) = default;
        NU_INLINE SpotLightComponent() = default; 
        SpotLight Light;
    };

    // rigid body component
    struct RigidBodyComponent
    {
        NU_INLINE RigidBodyComponent(const RigidBodyComponent&) = default;
        NU_INLINE RigidBodyComponent() = default;
        RigidBody3D RigidBody;
    };

    // Transform Component
    struct TransformComponent
    {
        NU_INLINE TransformComponent(const TransformComponent&) = default;
        NU_INLINE TransformComponent() = default;
        Transform3D Transform;
    };

    // collider component
    struct ColliderComponent 
    {
        NU_INLINE ColliderComponent(const ColliderComponent&) = default;
        NU_INLINE ColliderComponent() = default; 
        Collider3D Collider;
    }; 

    // model animator
    struct AnimatorComponent 
    { 
        NU_INLINE AnimatorComponent(const AnimatorComponent&) = default;
        NU_INLINE AnimatorComponent() = default; 
        Animator3D Animator;
    };


    // Camera Component
    struct CameraComponent
    {
        NU_INLINE CameraComponent(const CameraComponent&) = default;
        NU_INLINE CameraComponent() = default;
        Camera3D Camera;
    };
    
    // skybox component
    struct SkyboxComponent 
    {
        NU_INLINE SkyboxComponent(const SkyboxComponent&) = default;
        NU_INLINE SkyboxComponent() = default; 
        Skybox Sky;
    };

    // model component
    struct ModelComponent 
    { 
        NU_INLINE ModelComponent(const ModelComponent&) = default;
        NU_INLINE ModelComponent() = default; 
        PbrMaterial Material; 
        Model3D Model; 
    };

    // Mesh Component
    struct MeshComponent
    {
        NU_INLINE MeshComponent(const MeshComponent&) = default;
        NU_INLINE MeshComponent() = default;
        PbrMaterial Material;
        Mesh3D Mesh;
    };

    // Common Component
    struct EnttComponent
    {
        NU_INLINE EnttComponent(const EnttComponent&) = default;
        NU_INLINE EnttComponent() = default;
        std::string Name = "Untitled";
    };

    // base entity
    struct Entity
    {
        NU_INLINE Entity(EntityRegistry* registry, EntityID entity)
            : m_Registry(registry), m_EnttID(entity)
        {}

        NU_INLINE Entity(EntityRegistry* registry) : m_Registry(registry)
        {
            m_EnttID = m_Registry->create();
        }

        NU_INLINE virtual ~Entity() = default;
        NU_INLINE Entity() = default;

        NU_INLINE operator EntityID()
        {
            return m_EnttID;
        }

        NU_INLINE operator bool()
        {
            return m_Registry != nullptr && m_Registry->valid(m_EnttID);
        }

        NU_INLINE EntityID ID()
        {
            return m_EnttID;
        }

        // ++

        template<typename T, typename... Args>
        NU_INLINE T& Attach(Args&&... args)
        {
            return m_Registry->get_or_emplace<T>(m_EnttID, std::forward<Args>(args)...);
        }

        template<typename T>
        NU_INLINE void Detach()
        {
            m_Registry->remove<T>(m_EnttID);
        }

        NU_INLINE void Destroy()
        {
            if(m_Registry) { m_Registry->destroy(m_EnttID); }
        }

        template<typename T>
        NU_INLINE bool Has()
        {
            return m_Registry != nullptr && m_Registry->all_of<T>(m_EnttID);
        }

        template<typename T>
        NU_INLINE T& Get()
        {
            return m_Registry->get<T>(m_EnttID);
        }
    protected:
        EntityRegistry* m_Registry = nullptr;
        EntityID m_EnttID = NENTT;
    };
}