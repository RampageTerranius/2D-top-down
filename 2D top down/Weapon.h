#pragma once

#include <string>

#include "Projectile.h"

class Weapon
{
public:
	std::string name;
	int damage;
	int impact;
	int totalAmmo;
	float reloadTime;
	float projectileSpeed;
	int projectileDistance;
	ProjectileType BulletType;
};