#pragma once 
#include <queue> 
#include <vector> 
#include <string> 
#include <bitset> 
#include <memory> 
#include <sstream> 
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

// include spdlog
#define FMT_HEADER_ONLY
#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// import, export
#ifdef NU_EXPORT
    #ifdef _MSC_VER
        #define NU_API __declspec(dllexport)
    #else
        #define NU_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define NU_API __declspec(dllimport)
    #else
        #define NU_API
    #endif
#endif

// runtime assertion
#define NU_ASSERT assert

// static(compile) assertion
#if defined(__clang__) || defined(__gcc__)
    #define NU_STATIC_ASSERT _Static_assert
#else
    #define NU_STATIC_ASSERT static_assert
#endif

// function inlining
#if defined(__clang__) || defined(__gcc__)
    #define NU_INLINE __attribute__((always_inline)) inline
    #define NU_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
    #define NU_INLINE __forceinline
    #define NU_NOINLINE __declspec(noinline)
#else
    #define NU_INLINE inline
    #define NU_NOINLINE
#endif

// core features
namespace Nu
{
    // runtime type
    template<typename T>
    NU_INLINE constexpr uint32_t TypeID()
    {
        return static_cast<uint32_t>(reinterpret_cast<std::uintptr_t>(&typeid(T)));
    }

    // console logging
    struct NU_API Logger
    {
        using SPDLog = std::shared_ptr<spdlog::logger>;

        NU_INLINE Logger()
        {
            m_SPD = spdlog::stdout_color_mt("stdout");
            spdlog::set_level(spdlog::level::trace);
            spdlog::set_pattern("%^[%T]: [#%t] %v%$");
        }

        NU_INLINE static SPDLog& Ref()
        {
            static Logger logger;
            return logger.m_SPD;
        }

        private:
        SPDLog m_SPD;
    };
}

    // logging macros
#ifdef NU_ENABLE_LOG
    #define NU_TRACE(...) Nu::Logger::Ref()->trace(__VA_ARGS__)
    #define NU_DEBUG(...) Nu::Logger::Ref()->debug(__VA_ARGS__)
    #define NU_INFO(...)  Nu::Logger::Ref()->info(__VA_ARGS__) 
    #define NU_WARN(...)  Nu::Logger::Ref()->warn(__VA_ARGS__) 
    #define NU_ERROR(...) Nu::Logger::Ref()->error(__VA_ARGS__) 
    #define NU_FATAL(...) Nu::Logger::Ref()->critical(__VA_ARGS__)
#else
    #define NU_TRACE
    #define NU_DEBUG
    #define NU_ERROR
    #define NU_FATAL
    #define NU_INFO
    #define NU_WARN
#endif

// free allocated memory
#define NU_DELETE(ptr) if(ptr != nullptr) { delete (ptr); ptr = nullptr; }

// Detect Opengl Errors
GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        NU_FATAL("{} | {} ({})", error, file, line);
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 