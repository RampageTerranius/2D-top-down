#pragma once

#include "Entity.h"
#include "Weapon.h"

class Character : public Entity
{
public:
	Weapon* weapon;
	int reloadTimer;
	int ammoLeft;
	int fireTimer;
	float directionFacing;
	bool Render();
};

class Player : public Character
{
public:
	std::string name;

	int health;

	float currentRecoil;
	bool isFiring;

	int xVel;// -1 = left 0 = none 1 = right
	int yVel;// -1 = up 0 = none 1 = down
	
	float baseMovementVel = 4;
	float dodgeVel = 24;
	float dodgeVelDrop = 2;

	float currentMovementVel = baseMovementVel;

	int dodgesLeft = 3;
	int totalDodges = 3;
	int dodgeBaseRechargeTime = 120;
	int dodgeChargeTimer;
	
	void MovePlayerAccordingToInput();	
	void FireWeapon();
	void ReloadWeapon();
	void RenderAimer();
};

class Players
{
private:
	std::vector<Player*> playerList;

public:
	Player* CreatePlayer(std::string playerName);
	void DeletePlayer(std::string playerName);
	Player* GetPlayer(std::string playerName);
	void HandlePlayerEvents();
	void RenderAllPlayers();
};