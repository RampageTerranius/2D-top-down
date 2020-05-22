#pragma once

#include "ProjectileType.h"
#include "ReloadType.h"

#include <string>
#include <vector>

enum class FireType
{
	FullAuto,
	SemiAuto
};

// TODO: projectileDistance does not currently function.
class Weapon
{
public:
	Weapon();

	std::string name;
	int damage;
	int totalAmmo;
	int fireRate;
	int reloadTime;
	float projectileSpeed;
	float deviation;
	int bulletsPerShot;
	int projectileDistance;
	ProjectileType bulletType;
	ReloadType reloadType;
	FireType fireType;
};

class Weapons
{
public:
	std::vector<Weapon*> weaponList;
	void AddWeapon(Weapon* weapon);
	void RemoveWeapon(std::string wepName);
	void RemoveAllWeapons();
	Weapon* GetWeapon(std::string wepName);
};