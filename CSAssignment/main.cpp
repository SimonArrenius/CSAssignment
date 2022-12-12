#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"
#include "Utilities.h"

using namespace std;

bool EventHandler(int* right, int* down)
{
	SDL_Event event;
	int scancode;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
		{
			scancode = event.key.keysym.scancode;

			if (scancode == SDL_SCANCODE_ESCAPE)
				return false;

			if (scancode == SDL_SCANCODE_A)
				*right = -1;
			if (scancode == SDL_SCANCODE_D)
				*right = 1;
			if (scancode == SDL_SCANCODE_W)
				*down = -1;
			if (scancode == SDL_SCANCODE_S)
				*down = 1;

			break;
		}

		case SDL_KEYUP:
		{
			scancode = event.key.keysym.scancode;

			if (scancode == SDL_SCANCODE_A)
				*right = 0;
			if (scancode == SDL_SCANCODE_D)
				*right = 0;
			if (scancode == SDL_SCANCODE_W)
				*down = 0;
			if (scancode == SDL_SCANCODE_S)
				*down = 0;

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				;
			}
			break;
		}
		}
	}
	return true;
}


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.1,", 1280, 720);

	SDL_Texture* Asteroid = window.loadTexture("Textures/Asteroid.png");
	SDL_Texture* Ship = window.loadTexture("Textures/Ship.png");

	vector<Entity> entities = {Entity(Vector2f(0, 0), Asteroid),
							   Entity(Vector2f(30, 5), Asteroid),
							   Entity(Vector2f(30, 30), Asteroid)};
	{
		Entity asteroids(Vector2f(100, 50), Asteroid);

		entities.push_back(asteroids);
	}

	Entity player = { Entity(Vector2f(50, 50), Ship)};

	bool gameRunning = true;

	SDL_Event event;

	const float deltaTime = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utilities::hireTimeInSeconds();

	while (gameRunning)
	{
		int startTicks = SDL_GetTicks();

		float newTime = utilities::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= deltaTime)
		{
			accumulator -= deltaTime;
		}

		const float alpha = accumulator / deltaTime;

		int down = 0;
		int right = 0;

		gameRunning = EventHandler(&right, &down);
		player.pos.x += right * 700 * deltaTime;
		player.pos.y += down * 700 * deltaTime;

		//entities.pos.x += right * 500 * deltaTime;

		window.clear();

			for (Entity& a : entities)
			{
				window.render(a);
			}

			window.render(player);

			cout << utilities::hireTimeInSeconds() << endl;

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);	
	}
	window.cleanUp();
	SDL_Quit();

	return 0;
}


