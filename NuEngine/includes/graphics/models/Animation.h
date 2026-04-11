#pragma once
#include "Helper.h"

namespace Nu
{
    struct Animation
    {
		float Duration = 0.0f;
		float Speed = 1.0f;
        std::string Name;
	};

    struct KeyFrame
    {
        glm::vec3 Position = glm::vec3(0.0f);
		glm::quat Rotation = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);
        float TimeStamp = 0.0f;
    };

    struct Joint
    {
		std::vector<Joint> Children;
        std::vector<KeyFrame> Keys;
        std::string Name;
        glm::mat4 Offset; // inverse transformation matrix, used to transform the joints from local to global space
        int32_t Index;
	};
}