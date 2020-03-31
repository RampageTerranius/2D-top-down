#pragma once

#include <string>

#include "Projectile.h"

class Weapon
{
public:
	std::string name;
	int damage;
	int totalAmmo;
	float fireRate;
	float reloadTime;
	float projectileSpeed;
	int projectileDistance;
	ProjectileType BulletType;
};