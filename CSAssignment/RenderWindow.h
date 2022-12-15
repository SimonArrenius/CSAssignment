#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"

class RenderWindow
{
public: 
	RenderWindow(const char* p_title, int p_w, int p_h);
	void render(float x, float y, float w, float h, SDL_Texture* texture);
	SDL_Texture* loadTexture(const char* p_filePath);

	int getRefreshRate();

	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};