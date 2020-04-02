#include "Weapon.h"
#include "globals.h"

void Weapons::AddWeapon(Weapon* weapon)
{
	if (weapon != nullptr)
	{
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
		debug.Log("Weapon", "AddWeapon", "ProjectileDistance: " + std::to_string(weapon->projectileDistance));
		debug.Log("Weapon", "AddWeapon", "BulletType: " + std::to_string(weapon->bulletType));
		debug.Log("Weapon", "AddWeapon", "fireType: " + std::to_string(weapon->fireType));
	}
}
void Weapons::RemoveWeapon(std::string wepName)
{
	int i = 0;

	for (Weapon* wep : weaponList)
		if (wep->name == wepName)
		{
			weaponList.erase(weaponList.begin() + i);
			debug.Log("Weapon", "RemoveWeapon", "Removed a weapon");

			return;
		}
		else
			i++;
}

Weapon* Weapons::GetWeapon(std::string wepName)
{
	for (Weapon* wep : weaponList)
		if (wep->name == wepName)
			return wep;

		return nullptr;
}