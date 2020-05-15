#include "Weapon.h"
#include "globals.h"

void Weapons::AddWeapon(Weapon* weapon)
{
	if (weapon != nullptr)
	{
		// Drop the projectile speed by a factor of 100 or bullets will move at mach 10.
		weapon->projectileSpeed /= 100;

		// Drop the recoil control rate by the firerate to keep it consistant no matter the fire rate.
		//weapon->recoilControlRate /= weapon->fireRate;

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
		debug.Log("Weapon", "AddWeapon", "MaxDeviation: " + std::to_string(weapon->maxDeviation));
		debug.Log("Weapon", "AddWeapon", "Recoil: " + std::to_string(weapon->recoil));
		debug.Log("Weapon", "AddWeapon", "RecoilControlRate: " + std::to_string(weapon->recoilControlRate));
		debug.Log("Weapon", "AddWeapon", "BulletsPerShot: " + std::to_string(weapon->bulletsPerShot));
		debug.Log("Weapon", "AddWeapon", "ProjectileDistance: " + std::to_string(weapon->projectileDistance));
		debug.Log("Weapon", "AddWeapon", "BulletType: " + std::to_string(weapon->bulletType));
		debug.Log("Weapon", "AddWeapon", "fireType: " + std::to_string(weapon->fireType));
		debug.Log("Weapon", "AddWeapon", "reloadType: " + std::to_string(weapon->reloadType));
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

bool Weapons::GetNextWeapon(Weapon*& userWep)
{
	for (int i = 0; i < weaponList.size(); i++)
		if (weaponList[i]->name == userWep->name)
			if (i < weaponList.size() - 1)// If we are not at the last weapon then get the next weapon.
			{
				userWep = weaponList[i + 1];
				return true;
			}
			else// If we ARE at the last weapon then get the first.
			{
				userWep = weaponList[0];
				return true;
			}

	return false;
}

bool Weapons::GetLastWeapon(Weapon*& userWep)
{
	for (int i = 0; i < weaponList.size(); i++)
		if (weaponList[i]->name == userWep->name)
			if (i > 0)// If we are not at the first weapon then get the previous weapon.
			{
				userWep = weaponList[i - 1];
				return true;
			}
			else// If we ARE at the first weapon then get the last.
			{
				userWep = weaponList[weaponList.size() - 1];
				return true;
			}

	return false;
}