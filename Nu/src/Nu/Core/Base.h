#pragma once

#include <memory>

namespace Nu {

	void InitializeCore();
	void ShutdownCore();
}

#ifdef NM_DEBUG
	#define NM_ENABLE_ASSERTS
#endif

#ifdef NM_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
		#ifdef NM_BUILD_DLL
			#define NU_API __declspec(dllexport)
		#else
			#define NU_API __declspec(dllimport)
		#endif
	#else
		#define NU_API
	#endif
#else
	#error Nu only supports Windows!
#endif

#ifdef NM_ENABLE_ASSERTS
	#define NM_ASSERT(x, ...) { if(!(x)) { NM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NM_CORE_ASSERT(x, ...) { if(!(x)) { NM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NM_ASSERT(x, ...)
	#define NM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NM_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)