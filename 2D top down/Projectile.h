#pragma once

#include "Entity.h"
#include "Weapon.h"
#include "ProjectileType.h"
#include "Vector2D.h"

#include <vector>

class Projectile : public Entity
{
public:
	Projectile();

	bool CalcProjectile();

	ProjectileType type;
	int damage;
	int maxDistance;
	Player* Owner;
	Vector2D target = Vector2D{ 0, 0 };
	Vector2D start = Vector2D{ 0, 0 };
	float velocity;

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
	void CreateProjectile(Vector2D start, Vector2D end, Weapon* weapon, Player* owner);
	void RenderAllProjectiles();
	void DestroyProjectile(Projectile* proj);
	void DestroyAllProjectiles();

	ProjectileLinkedList projectileList;
	bool debugProjectiles = false;
};