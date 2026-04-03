#pragma once
#include "common/Event.h" // this inclusion order is important for later (opengl!)
#include <GLFW/glfw3.h>

namespace Nu
{
    struct WindowInputs
    {
        std::bitset<GLFW_MOUSE_BUTTON_LAST> Mouse;
        std::bitset<GLFW_KEY_LAST> Keys;
        double MouseX = 0.0;
        double MouseY = 0.0;
    };
}