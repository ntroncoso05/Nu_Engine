#include "nupch.h"
#include "Base.h"

#include "Log.h"

#define NU_BUILD_ID "v0.1a"

namespace Nu {

	void InitializeCore()
	{
		Nu::Log::Init();

		NM_CORE_TRACE("Nu Engine {}", NU_BUILD_ID);
		NM_CORE_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		NM_CORE_TRACE("Shutting down...");
	}

}