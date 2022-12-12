#pragma once

#include <SDL.h>

namespace utilities
{
	inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;
	}
}