#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "math.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	Vector2f pos;
	Vector2f& getPos()
	{
		return pos;
	}

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};