#pragma once

#include "Entity.h"
#include "Weapon.h"

class Character : public Entity
{
public:
	float directionFacing;
	bool Render();
};

class Player : public Character
{
public:
	std::string name;

	int health;

	Weapon* weapon;
	int reloadTimer;
	int ammoLeft;
	int fireTimer;
	float currentRecoil;
	bool isFiring;

	int xVel;// -1 = left 0 = none 1 = right
	int yVel;// -1 = up 0 = none 1 = down
	
	int walkVel = 2;
	int sprintVel = 5;

	bool sprinting;
	
	float velDropWhenOverMaxVel;

	void MovePlayerAccordingToInput();	
	void FireWeapon(SDL_Point aimLoc);
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