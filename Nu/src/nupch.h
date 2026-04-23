#pragma once

#ifdef NM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <memory>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include <fstream>

#include <Nu/Core/Base.h>
#include <Nu/Core/Log.h>
#include <Nu/Core/Events/Event.h>
