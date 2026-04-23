#pragma once

#include "Nu/Core/Base.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Nu {

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
#define NM_CORE_TRACE(...)	Nu::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NM_CORE_INFO(...)	Nu::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NM_CORE_WARN(...)	Nu::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NM_CORE_ERROR(...)	Nu::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NM_CORE_FATAL(...)	Nu::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Logging Macros
#define NM_TRACE(...)		Nu::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NM_INFO(...)		Nu::Log::GetClientLogger()->info(__VA_ARGS__)
#define NM_WARN(...)		Nu::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NM_ERROR(...)		Nu::Log::GetClientLogger()->error(__VA_ARGS__)
#define NM_FATAL(...)		Nu::Log::GetClientLogger()->critical(__VA_ARGS__)