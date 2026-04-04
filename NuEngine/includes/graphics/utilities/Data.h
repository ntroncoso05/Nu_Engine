#pragma once
#include "../models/Model.h"

namespace Nu
{
    // Transform
    struct Transform3D
    {
        NU_INLINE Transform3D(const Transform3D&) = default;
        NU_INLINE Transform3D() = default; 

        NU_INLINE glm::mat4 Matrix() const
        {
            return (glm::translate(glm::mat4(1.0f), Translate) *
                glm::toMat4(glm::quat(glm::radians(Rotation))) *
                glm::scale(glm::mat4(1.0f), Scale));
        }

        glm::vec3 Translate = glm::vec3(0.0f);
        glm::vec3 Rotation = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);
    };

    // Camera
    struct Camera3D
    {
        NU_INLINE Camera3D(const Camera3D&) = default;
        NU_INLINE Camera3D() = default;
        NU_INLINE glm::mat4 Frustum(const Transform3D& transform, float ratio) const
        {
            return Projection(ratio) * View(transform);
        }

        NU_INLINE glm::mat4 View(const Transform3D& transform) const
        {
            return glm::lookAt(transform.Translate, (transform.Translate + glm::vec3(0.0f, 0.0f, -1.0f)),
                glm::vec3(0.0f, 1.0f, 0.0f)) * glm::toMat4(glm::quat(glm::radians(transform.Rotation)));
        }

        NU_INLINE glm::mat4 Projection(float ratio) const
        {
            return glm::perspective(FOV, ratio, NearPlane, FarPlane);
        }

        float NearPlane = 0.3000f;
        float FarPlane = 1000.0f;
        float FOV = 45.0f;
    };    
}