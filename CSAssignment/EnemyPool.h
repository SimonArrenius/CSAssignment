#pragma once
#include <vector>
#include "math.h"
#include "RenderWindow.h"

class EnemyPool
{
public:
	EnemyPool(RenderWindow* rw, int p_w, int p_h);
	void render(RenderWindow* rw, float deltaTime);
	void allocateEnemy(int amount = 100);
	void spawnEnemy(int amount = 3);
	void deactivateEnemy(int removeIndex);

private:

	vector<Entity> entities;

	vector<Vector2f> positions;

	vector<Vector2f> velocities;


	int p_w; 
	int p_h;
	SDL_Texture* Asteroid;
	int active = 0;
};

