#pragma once

#include "ProjectileType.h"
#include "ReloadType.h"
#include "Audio.h"

#include <string>
#include <vector>

enum class FireType
{
	FullAuto,
	SemiAuto
};

class Weapon
{
public:
	Weapon();
	void PlayFireSound();

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
	int bulletsPerShot;
	int projectileDistance;
	ProjectileType bulletType;
	ReloadType reloadType;
	FireType fireType;
	Sound* fireSound;
	Sound* reloadSound;
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