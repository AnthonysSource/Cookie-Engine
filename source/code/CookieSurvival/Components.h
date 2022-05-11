#pragma once

#include "CookieEngine.h"

namespace Cookie {

	struct PlayerCharacterComponent {
		f32 m_Speed;
	};

	struct EnemyComponent {
		f32 m_Acceleration;
		Float3 m_Velocity;
	};

	struct SinglMainPlayerComponent {
		Float3 m_Position;
	};

} // namespace Cookie