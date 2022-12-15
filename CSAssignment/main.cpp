#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"
#include "Utilities.h"
#include "EnemyPool.h"

using namespace std;

bool EventHandler(int* right, int* down, EnemyPool* ePool)
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
			if (scancode == SDL_SCANCODE_F)
				ePool->spawnEnemy(10);

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

	int p_w = 1280;
	int p_h = 720;

	RenderWindow window("GAME v1.1,", p_w, p_h);

	EnemyPool ePool = EnemyPool(&window, p_w, p_h);

	SDL_Texture* Ship = window.loadTexture("Textures/Ship.png");


	Entity player = { Entity(Vector2f(50, 50), Ship) };

	bool gameRunning = true;

	SDL_Event event;

	ePool.spawnEnemy(10);

	while (gameRunning)
	{


		int down = 0;
		int right = 0;

		gameRunning = EventHandler(&right, &down, &ePool);
		player.pos.x += right * 5;// *deltaTime;
		player.pos.y += down * 5;// *deltaTime;

		//for (size_t i = 0; i < entities.size(); i++)
		//{
		//	entities[i].pos.x += 0 * 5;
		//	entities[i].pos.y += 1 * 5;
		//}

		window.clear();

			//for (Entity& a : entities)
			//{
			//	window.render(a);
			//}

		ePool.render(&window);

			window.render(player);

			cout << utilities::hireTimeInSeconds() << endl;

		window.display();
	}
	window.cleanUp();
	SDL_Quit();

	return 0;
}
