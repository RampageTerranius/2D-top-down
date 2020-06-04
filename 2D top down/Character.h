#pragma once

#include "Entity.h"
#include "Weapon.h"

class Character : public Entity
{
public:
	Character();

	void MoveBy(float x, float y);

	bool Render();
	void MoveCameraToHere();

	Vector2D directionFacing = { 0, 0 };
};

class Player : public Character
{
public:
	Player();

	void FireWeapon();
	void ReloadWeapon();
	void RenderAimer();
	void AddWeapon(Weapon* wep);
	void RemoveWeapon(int weaponIndex);
	void SwitchToNextWeapon();
	void SwitchToLastWeapon();	

	std::string name;

	int health;

	float currentRecoil;
	bool firedThisTick;
	bool firedLastTick;
	bool changedWeaponThisTick;
	bool changedWeaponLastTick;

	std::vector<Weapon*> weapon;
	int selectedWeapon;
	std::vector<int> ammoLeft;
	int reloadTimer;
	int fireTimer;

	int xVel;// -1 = left 0 = none 1 = right
	int yVel;// -1 = up 0 = none 1 = down
	
	float baseMovementVel;
	float dodgeVel;
	float dodgeVelDrop;

	float currentMovementVel;

	int dodgesLeft;
	int totalDodges;
	int dodgeBaseRechargeTime;
	int dodgeChargeTimer;
};

class Players
{
private:
	std::vector<Player*> playerList;

public:
	Player* CreatePlayer(std::string playerName);
	void DeletePlayer(std::string playerName);
	void DeleteAllPlayers();
	Player* GetPlayer(std::string playerName);
	void HandlePlayerEvents();
	void RenderAllPlayers();
};