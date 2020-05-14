#pragma once

#include "ProjectileType.h"
#include "ReloadType.h"

#include <string>
#include <vector>

enum FireType
{
	FIRETYPE_FULLAUTO,
	FIRETYPE_SEMIAUTO
};

// TODO: projectileDistance does not currently function.
class Weapon
{
public:
	std::string name;
	int damage;
	int totalAmmo;
	int fireRate;
	int reloadTime;
	float projectileSpeed;
	float deviation;
	float maxDeviation;
	float recoil;
	float recoilControlRate;
	int bulletsPerShot = 1;
	int projectileDistance;
	ProjectileType bulletType;
	ReloadType reloadType;
	FireType fireType;
};

class Weapons
{
private:
	std::vector<Weapon*> weaponList;

public:
	void AddWeapon(Weapon* weapon);
	void RemoveWeapon(std::string wepName);
	void RemoveAllWeapons();
	Weapon* GetWeapon(std::string wepName);
	bool GetNextWeapon(Weapon*& userWep);
	bool GetLastWeapon(Weapon*& userWep);
};