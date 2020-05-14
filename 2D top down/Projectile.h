#pragma once

#include "Entity.h"
#include "Weapon.h"
#include "ProjectileType.h"
#include "Character.h"
#include <vector>

class Projectile : public Object
{
public:
	Projectile();

	bool CalcProjectile();

	ProjectileType type;
	int damage;
	Player* Owner;
	SDL_Point targetPoint;
	float xStart;
	float yStart;
};

class Projectiles
{
public:
	void CalcAllProjectiles();
	void CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon, Player* owner);
	void RenderAllProjectiles();
	void DestroyProjectile(Projectile* proj);
	void DestroyAllProjectiles();

	std::vector<Projectile*> projectileList;
};