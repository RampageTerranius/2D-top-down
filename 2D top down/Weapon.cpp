#include "Weapon.h"

void Weapons::AddWeapon(Weapon* weapon)
{
	weaponList.push_back(weapon);
}
void Weapons::RemoveWeapon(std::string wepName)
{
	int i = 0;

	for (Weapon* wep : weaponList)
		if (wep->name == wepName)
		{
			weaponList.erase(weaponList.begin() + i);
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