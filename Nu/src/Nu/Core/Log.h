#pragma once

#include "Nu/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/ostream.h"

namespace nu {

	class NU_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core Logging Macros
#define NM_CORE_TRACE(...)	nu::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NM_CORE_INFO(...)	nu::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NM_CORE_WARN(...)	nu::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NM_CORE_ERROR(...)	nu::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NM_CORE_FATAL(...)	nu::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Logging Macros
#define NM_TRACE(...)		nu::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NM_INFO(...)		nu::Log::GetClientLogger()->info(__VA_ARGS__)
#define NM_WARN(...)		nu::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NM_ERROR(...)		nu::Log::GetClientLogger()->error(__VA_ARGS__)
#define NM_FATAL(...)		nu::Log::GetClientLogger()->critical(__VA_ARGS__)