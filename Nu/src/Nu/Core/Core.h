#pragma once

namespace Nu {

	void InitializeCore();
	void ShutdownCore();

}

#ifdef NU_BUILD_DLL
	#define NU_API __declspec(dllexport)
#else
	#define NU_API __declspec(dllimport)
#endif