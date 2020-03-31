#pragma once

#include "Entity.h"
#include <vector>

enum ProjectileType
{
	Bullet
};

class Projectile : public Object
{
public:
	ProjectileType type;
	float distanceLeft;

	bool CalcProjectile();
};

class Projectiles
{
public:
	std::vector<Projectile*> projectileList;

	void CalcAllProjectiles();
	Projectile* CreateProjectile(SDL_Point start, SDL_Point end);
	void RenderAllProjectiles();
	void DestroyProjectile(Projectile* proj);
};