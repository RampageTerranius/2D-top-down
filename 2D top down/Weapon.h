#pragma once

#include "ProjectileType.h"

#include <string>
#include <vector>

enum FireType
{
	FIRETYPE_FULLAUTO,
	FIRETYPE_SEMIAUTO
};

class Weapon
{
public:
	std::string name;
	int damage;
	int totalAmmo;
	float fireRate;
	float reloadTime;
	float projectileSpeed;
	float deviation;
	float maxDeviation;
	float recoil;
	float recoilControlRate;
	int projectileDistance;
	ProjectileType BulletType;
	FireType fireType;
};

class Weapons
{
private:
	std::vector<Weapon*> weaponList;

public:
	void AddWeapon(Weapon* weapon);
	void RemoveWeapon(std::string wepName);
	Weapon* GetWeapon(std::string wepName);
};