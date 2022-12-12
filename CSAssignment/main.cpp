#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"
#include "Utilities.h"

using namespace std;

int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0,", 1280, 720);

	SDL_Texture* Asteroid = window.loadTexture("Textures/Asteroid.png");

	vector<Entity> entities = {Entity(Vector2f(0, 0), Asteroid),
							   Entity(Vector2f(30, 5), Asteroid),
							   Entity(Vector2f(30, 30), Asteroid)};
	{
		Entity asteroids(Vector2f(100, 50), Asteroid);

		entities.push_back(asteroids);
	}

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
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			accumulator -= deltaTime;
		}

		const float alpha = accumulator / deltaTime;

		window.clear();

			for (Entity& a : entities)
			{
				window.render(a);
			}

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