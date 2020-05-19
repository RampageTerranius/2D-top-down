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
	int maxDistance;
	Player* Owner;
	SDL_Point targetPoint;
	float xStart;
	float yStart;

	Projectile* last = nullptr;
	Projectile* next = nullptr;
};

class ProjectileLinkedList
{
public:
	void PushBack(Projectile* data);
	bool DeleteBack();
	bool DeleteFront();
	bool Delete(Projectile* data);
	void Clear();

	Projectile* front = nullptr;
	Projectile* back = nullptr;

	int count = 0;
};

class Projectiles
{
public:
	void CalcAllProjectiles();
	void CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon, Player* owner);
	void RenderAllProjectiles();
	void DestroyProjectile(Projectile* proj);
	void DestroyAllProjectiles();

	ProjectileLinkedList projectileList;
};