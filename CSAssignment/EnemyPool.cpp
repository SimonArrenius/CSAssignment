#include "EnemyPool.h"


EnemyPool::EnemyPool(RenderWindow* rw, int p_w, int p_h)
{
	Asteroid = rw -> loadTexture("Textures/Asteroid.png");
	this->p_w = p_w;
	this->p_h = p_h;
	srand(time(NULL));
}

void EnemyPool::render(RenderWindow* rw)
{
	for (size_t i = 0; i < active; i++)
	{
		positions[i].x += velocities[i].x;
		positions[i].y += velocities[i].y;
		rw -> render(positions[i].x, positions[i].y, 100, 100, Asteroid);

		if (positions[i].x < 0 || positions[i].x > 1280 || positions[i].y < 0 || positions[i].y > 720)
		{
			deactivateEnemy(i);
		}
	}
	cout << "Active entities " << active << endl;
}

bool hasSpawned = false;

void EnemyPool::allocateEnemy(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		entities.emplace_back(Vector2f(rand() % p_w, rand() % p_h), Asteroid);
		positions.emplace_back(entities.back().pos.x, entities.back().pos.y);
		velocities.emplace_back((rand() % 10) - 5, 2);
	}
}

void EnemyPool::spawnEnemy(int amount)
{
	active += amount;
	while (active > entities.size())
	{
		allocateEnemy();
	}
	for (int i = active - amount; i < active; i++)
	{
		entities[i].pos.x = (rand() % p_w);
		entities[i].pos.y = (rand() % p_h);
		//positions[i] = (entities.back().pos);
		//positions.emplace_back(entities.back().pos.x, entities.back().pos.y);
		velocities[i].x = ((rand() % 10) - 5);
		velocities[i].y = 2;
	}
}

void EnemyPool::deactivateEnemy(int i)
{
		swap(entities[i], entities[active-1]);
		swap(positions[i], positions[active-1]);
		swap(velocities[i], velocities[active-1]);
		active--;
}