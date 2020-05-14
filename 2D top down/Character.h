#pragma once

#include "Entity.h"
#include "Weapon.h"

class Character : public Entity
{
public:
	Character();

	bool Render();

	Weapon* weapon;
	int reloadTimer;
	int ammoLeft;
	int fireTimer;
	float directionFacing;
	
};

class Player : public Character
{
public:
	Player();

	void MovePlayerAccordingToInput();
	void FireWeapon();
	void ReloadWeapon();
	void RenderAimer();

	std::string name;

	int health;

	float currentRecoil;
	bool isFiring;

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