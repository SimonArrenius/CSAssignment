#include "ProjectileHandle.h"



ProjectileHandle::ProjectileHandle(RenderWindow* rw, int p_w, int p_h)
{
	Asteroid = rw->loadTexture("Textures/Asteroid.png");
	this->p_w = p_w;
	this->p_h = p_h;
	srand(time(NULL));
}

void ProjectileHandle::render(RenderWindow* rw)
{
	for (size_t i = 0; i < active; i++)
	{
		rw->render(positions[i].x, positions[i].y, 16, 16, Asteroid);

		if (positions[i].x < 0 || positions[i].x > 1280 || positions[i].y < 0 || positions[i].y > 720)
		{
			deactivateProj(i);
		}
	}
	cout << "Active entities: " << active << endl;
}

void ProjectileHandle::pMovement(float deltaTime)
{
	for (size_t i = 0; i < active; i++)
	{
		positions[i].x += velocities[i].x * deltaTime;
		positions[i].y += velocities[i].y * deltaTime;
	}
}

void ProjectileHandle::allocateProj(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		entities.emplace_back(Entity(Vector2f(0, 0), Asteroid));
		positions.emplace_back(Vector2f(0, 0));
		velocities.emplace_back(Vector2f(0, 0));
	}
}

void ProjectileHandle::spawnProj(Vector2f playerpos, Vector2f dest, int amount)
{
	active += amount;
	while (active > entities.size())
	{
		allocateProj();
	}
	for (int i = active - amount; i < active; i++)
	{
		entities[i].pos = (playerpos);
		entities[i].pos.x += 40;
		entities[i].pos.y += 40;
		positions[i] = (entities[i].pos);
		velocities[i].x = (dest.x - playerpos.x);
		velocities[i].y = (dest.y - playerpos.y);
	}
}

void ProjectileHandle::deactivateProj(int i)
{
	swap(entities[i], entities[active - 1]);
	swap(positions[i], positions[active - 1]);
	swap(velocities[i], velocities[active - 1]);
	active--;
}