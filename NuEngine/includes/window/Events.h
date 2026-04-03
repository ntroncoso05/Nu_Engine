#pragma once
#include "Inputs.h"

namespace Nu
{
    // Window Events
    struct WindowMaximizeEvent {};
    struct WindowIconifyEvent {};
    struct WindowRestoreEvent {};
    struct WindowCloseEvent {};

    struct WindowResizeEvent
    {
        WindowResizeEvent(uint32_t w, uint32_t h): Width(w), Height(h) {}        
        int32_t Height = 0;
        int32_t Width = 0;
    };

    // Key Events
    struct KeyReleaseEvent
    {
        KeyReleaseEvent(int32_t key): Key(key) {}
        int32_t Key = -1;
    };

    struct KeyPressEvent
    {
        KeyPressEvent(int32_t key): Key(key) {}
        int32_t Key = -1;
    };

    struct KeyRepeatEvent
    {
        KeyRepeatEvent(int32_t key): Key(key) {}
        int32_t Key = -1;
    };

    // Mouse Events
    struct MouseReleaseEvent
    {
        MouseReleaseEvent(int32_t b): Button(b) {}
        int32_t Button = -1;
    };

    struct MouseDownEvent
    {
        MouseDownEvent(int32_t b): Button(b) {}
        int32_t Button = -1;
    };

    struct MouseDragEvent
    {
        MouseDragEvent(double dx, double dy): DeltaX(dx), DeltaY(dy) {}
        double DeltaX = 0.0, DeltaY = 0.0;
    };

    struct MouseMotionEvent
    {
        MouseMotionEvent(double x, double y): TargetX(x), TargetY(y) {}
        double TargetX = 0.0, TargetY = 0.0;
    };
    
    struct MouseWheelEvent
    {
        MouseWheelEvent(double sx, double sy): ScrollX(sx), ScrollY(sy) {}
        double ScrollX = 0.0, ScrollY = 0.0;
    };
}