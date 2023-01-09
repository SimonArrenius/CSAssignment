#pragma once
#include <vector>
#include "math.h"
#include "RenderWindow.h"

class ProjectileHandle
{
public:
	ProjectileHandle(RenderWindow* rw, int p_w, int p_h);
	void render(RenderWindow* rw);
	void pMovement(float deltaTime);
	void allocateProj(int amount = 100);
	void spawnProj(Vector2f playerpos, Vector2f dest, int amount = 1);
	void deactivateProj(int removeIndex);

private:

	vector<Entity> entities;

	vector<Vector2f> positions;
	
	vector<Vector2f> velocities;


	int p_w;
	int p_h;
	SDL_Texture* Asteroid;
	int active = 0;
};

