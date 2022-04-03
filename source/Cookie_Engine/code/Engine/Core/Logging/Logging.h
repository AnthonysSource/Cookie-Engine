#pragma once

#include <spdlog/spdlog.h>

namespace Cookie {
namespace Log {

	void Init();
	void Shutdown();

	namespace Internal {
		extern std::shared_ptr<spdlog::logger> engineLogger;
	}

} // namespace Log

} // namespace Cookie

#ifdef COOKIE_LOGGING
#define CKE_LOG_INFO(...)                                                                          \
	{ Cookie::Log::Internal::engineLogger->info(__VA_ARGS__) ; }
#else
#define CKE_LOG_INFO(...)
#define CKE_LOG_WARNING(...)
#define CKE_LOG_ERROR(...)
#define CKE_LOG_ASSERT(...)
#endif