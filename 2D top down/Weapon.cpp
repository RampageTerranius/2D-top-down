#include "Weapon.h"
#include "globals.h"
#include "Debug.h"

Weapon::Weapon()
{
	this->name = std::string();
	this->damage = 0;
	this->totalAmmo = 0;
	this->fireRate = 0;
	this->reloadTime = 0;
	this->projectileSpeed = 0.0f;
	this->deviation = 0.0f;
	this->bulletsPerShot = 0;
	this->projectileDistance = 0;
	this->bulletType = ProjectileType::Bullet;
	this->reloadType = ReloadType::Clip;
	this->fireType = FireType::FullAuto;
	this->fireSound = nullptr;
	this->reloadSound = nullptr;
}

void Weapon::PlayFireSound()
{
	if (this->fireSound != nullptr)
	{	
		this->fireSound->Stop();
		this->fireSound->Play();
	}
}

void Weapons::AddWeapon(Weapon* weapon)
{
	if (weapon != nullptr)
	{
		// Push the new weapon into the list then send a log of the weapon to the console.
		weaponList.push_back(weapon);

		debug.Log("Weapon", "AddWeapon", "--Weapon added with following stats--");
		debug.Log("Weapon", "AddWeapon", "Name: " + weapon->name);
		debug.Log("Weapon", "AddWeapon", "Damage: " + std::to_string(weapon->damage));
		debug.Log("Weapon", "AddWeapon", "TotalAmmo: " + std::to_string(weapon->totalAmmo));
		debug.Log("Weapon", "AddWeapon", "FireRate: " + std::to_string(weapon->fireRate));
		debug.Log("Weapon", "AddWeapon", "ReloadTime: " + std::to_string(weapon->reloadTime));
		debug.Log("Weapon", "AddWeapon", "ProjectileSpeed: " + std::to_string(weapon->projectileSpeed));
		debug.Log("Weapon", "AddWeapon", "Deviation: " + std::to_string(weapon->deviation));
		debug.Log("Weapon", "AddWeapon", "BulletsPerShot: " + std::to_string(weapon->bulletsPerShot));
		debug.Log("Weapon", "AddWeapon", "ProjectileDistance: " + std::to_string(weapon->projectileDistance));
		debug.Log("Weapon", "AddWeapon", "BulletType: " + std::to_string(static_cast<int> (weapon->bulletType)));
		debug.Log("Weapon", "AddWeapon", "fireType: " + std::to_string(static_cast<int> (weapon->fireType)));
		debug.Log("Weapon", "AddWeapon", "reloadType: " + std::to_string(static_cast<int> (weapon->reloadType)));
	}
}

void Weapons::RemoveWeapon(std::string wepName)
{
	int i = 0;

	// Check all weapons and find the first one with the given name, then remove it.
	for (Weapon* wep : weaponList)
		if (wep->name == wepName)
		{			
			weaponList.erase(weaponList.begin() + i);
			delete wep;
			debug.Log("Weapons", "RemoveWeapon", "Removed a weapon");

			return;
		}
		else
			i++;
}

void Weapons::RemoveAllWeapons()
{
	int i = 0;

	// Check all weapons and find the first one with the given name, then remove it.
	for (Weapon* wep : weaponList)	
		delete wep;	

	weaponList.clear();

	debug.Log("Weapons", "RemoveAllWeapons", "Removed all weapons");
}

Weapon* Weapons::GetWeapon(std::string wepName)
{
	for (Weapon* wep : weaponList)
		if (wep->name == wepName)
			return wep;

		return nullptr;
}