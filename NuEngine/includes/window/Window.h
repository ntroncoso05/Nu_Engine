#pragma once
#include "Events.h"

namespace Nu
{
    struct AppWindow
    {
        NU_INLINE AppWindow(EventDispatcher* dispatcher, int32_t width, int32_t height, const char* title)
            : m_Dispatcher(dispatcher)
        {
            if(glfwInit() != GLFW_TRUE)
            {
                NU_FATAL("glfwInit() failed!");
                exit(EXIT_FAILURE);
            }

            glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 4??

            auto display =glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwWindowHint(GLFW_REFRESH_RATE, display->refreshRate);
            glfwWindowHint(GLFW_GREEN_BITS, display->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, display->blueBits);
            glfwWindowHint(GLFW_RED_BITS, display->redBits);
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            m_Handle = glfwCreateWindow(width, height, title, NULL, NULL);
            if(m_Handle == NULL)
            {
                NU_FATAL("Failed to initialize app-window!");
                exit(EXIT_FAILURE);
            }

            // set user data
            glfwSetWindowUserPointer(m_Handle, this);

            // binding Callbacks
            glfwSetWindowMaximizeCallback(m_Handle, OnMaximize);
            glfwSetFramebufferSizeCallback(m_Handle, OnResize);
            glfwSetWindowIconifyCallback(m_Handle, OnIconify);
            glfwSetMouseButtonCallback(m_Handle, OnMouse);
            glfwSetWindowCloseCallback(m_Handle, OnClose);
            glfwSetCursorPosCallback(m_Handle, OnMotion);
            glfwSetScrollCallback(m_Handle, OnWheel);
            glfwSetKeyCallback(m_Handle, OnKey);
            glfwSetErrorCallback(OnError);

            // create opengl context
            glfwMakeContextCurrent(m_Handle);

            // buffer swap interval
            glfwSwapInterval(1);
        }

        NU_INLINE ~AppWindow()
        {
            glfwDestroyWindow(m_Handle);
            glfwTerminate();
        }

        NU_INLINE GLFWwindow* Handle()
        {
            return m_Handle;
        }

        NU_INLINE bool PollEvents()
        {
            glfwPollEvents();
            m_Dispatcher->PollEvents();
            glfwSwapBuffers(m_Handle);
            return (!glfwWindowShouldClose(m_Handle));
        }

        NU_INLINE bool IsKey(int32_t key)
        {
            if(key >=0 && key <= GLFW_KEY_LAST)
                return m_Inputs.Keys.test(key);
            return false;
        }

        NU_INLINE bool IsMouse(int32_t button)
        {
            if(button >=0 && button <= GLFW_MOUSE_BUTTON_LAST)
                return m_Inputs.Mouse.test(button);
            return false;
        }
    private:
        NU_INLINE static void OnKey(GLFWwindow* window, int32_t key, int32_t, int32_t action, int32_t)
        {
            AppWindow* self = GetUserData(window);
            if(key >= 0 && key <= GLFW_KEY_LAST)
            {
                switch (action)
                {
                case GLFW_RELEASE:
                    self->m_Dispatcher->PostEvent<KeyReleaseEvent>(key);
                    self->m_Inputs.Keys.reset(key);
                break;
                case GLFW_PRESS:
                    self->m_Dispatcher->PostEvent<KeyPressEvent>(key);
                    self->m_Inputs.Keys.set(key);
                break;
                case GLFW_REPEAT:
                    self->m_Dispatcher->PostEvent<KeyRepeatEvent>(key);
                    self->m_Inputs.Keys.set(key);
                break;
                }
                return;
            }
            NU_ERROR("Invalid key code detected: ({})", key);
        }

        NU_INLINE static void OnMouse(GLFWwindow* window, int32_t button, int32_t action, int32_t)
        {
            AppWindow* self = GetUserData(window);
            if(button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST)
            {
                switch(action)
                {
                case GLFW_PRESS:
                    self->m_Dispatcher->PostEvent<MouseDownEvent>(button);
                    self->m_Inputs.Mouse.set(button);
                break;
                case GLFW_RELEASE:
                    self->m_Dispatcher->PostEvent<MouseReleaseEvent>(button);
                    self->m_Inputs.Mouse.reset(button);
                break;
                }
                return;
            }
            NU_WARN("Invalid key code detected: ({})", button);
        }

        NU_INLINE static void OnResize(GLFWwindow* window, int32_t width, int32_t height)
        {
            GetUserData(window)->m_Dispatcher->PostEvent<WindowResizeEvent>(width, height);
        }

        NU_INLINE static void OnMotion(GLFWwindow* window, double x, double y)
        {
            AppWindow* self = GetUserData(window);
            self->m_Dispatcher->PostEvent<MouseMotionEvent>(x, y);

            if(self->m_Inputs.Mouse.test(GLFW_MOUSE_BUTTON_LEFT))
            {
                self->m_Dispatcher->PostEvent<MouseDragEvent>((self->m_Inputs.MouseX - x), (self->m_Inputs.MouseY - y));
            }

            self->m_Inputs.MouseX = x;
            self->m_Inputs.MouseY = y;
        }

        NU_INLINE static void OnWheel(GLFWwindow* window, double x, double y)
        {
            GetUserData(window)->m_Dispatcher->PostEvent<MouseWheelEvent>(x, y);
        }

        NU_INLINE static void OnMaximize(GLFWwindow* window, int32_t action)
        {
            if(action)
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowMaximizeEvent>();
            }
            else
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowRestoreEvent>();
            }
        }

        NU_INLINE static void OnIconify(GLFWwindow* window, int32_t action)
        {
            if(action)
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowIconifyEvent>();
            }
            else
            {
                GetUserData(window)->m_Dispatcher->PostEvent<WindowRestoreEvent>();
            }
        }

        NU_INLINE static void OnError(int32_t code, const char* msg)
        {
            NU_ERROR("[GLFW]: [{}] {}", code, msg);
        }

        NU_INLINE static void OnClose(GLFWwindow* window)
        {
            GetUserData(window)->m_Dispatcher->PostEvent<WindowCloseEvent>();
        }

        NU_INLINE static AppWindow* GetUserData(GLFWwindow* window)
        {
            return static_cast<AppWindow*>(glfwGetWindowUserPointer(window));
        }

    private:
        EventDispatcher* m_Dispatcher;
        WindowInputs m_Inputs;
        GLFWwindow* m_Handle;
    };
}