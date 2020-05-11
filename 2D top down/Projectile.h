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

	void CalcProjectile();

	ProjectileType type;
	float distanceLeft;
	int damage;
	Player* Owner;
};

class Projectiles
{
public:
	void CalcAllProjectiles();
	Projectile* CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon, Player* owner);
	void RenderAllProjectiles();
	void DestroyProjectile(Projectile* proj);

	std::vector<Projectile*> projectileList;
};