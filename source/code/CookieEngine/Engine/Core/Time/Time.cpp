#include "Time.h"

#include <GLFW/glfw3.h>
#include <chrono>

namespace Cookie {

	//-------------------------------------------------------------------------

	u64 PlatformClock::GetTimeInNanoseconds() {
		auto const t = std::chrono::high_resolution_clock::now();
		u64 nanosec = t.time_since_epoch().count();
		return nanosec;
	}

	//-------------------------------------------------------------------------

	EngineClock g_EngineClock;

	//-------------------------------------------------------------------------

	void EngineClock::Init() {
		m_TimeData.m_SecondsUpTimeLastUpdate = glfwGetTime();
		m_TimeData.m_SecondsUpTime = m_TimeData.m_SecondsUpTimeLastUpdate;

		m_TimeData.m_FrameNumber = 0;
	}

	void EngineClock::Update() {
		m_TimeData.m_SecondsUpTime = glfwGetTime();
		m_TimeData.m_DeltaTime = m_TimeData.m_SecondsUpTime - m_TimeData.m_SecondsUpTimeLastUpdate;
		m_TimeData.m_SecondsUpTimeLastUpdate = m_TimeData.m_SecondsUpTime;

		++m_TimeData.m_FrameNumber;
	}

} // namespace Cookie