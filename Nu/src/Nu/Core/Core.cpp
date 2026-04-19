#include "Core.h"

#include "Log.h"

#include <Windows.h>

#define NU_BUILD_ID "v0.1a"

namespace Nu {

	void InitializeCore()
	{
		nu::Log::Init();

		NM_CORE_TRACE("Nu Engine {}", NU_BUILD_ID);
		NM_CORE_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		NM_CORE_TRACE("Shutting down...");
	}

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Nu::InitializeCore();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Nu::ShutdownCore();
		break;
	}
	return TRUE;
}