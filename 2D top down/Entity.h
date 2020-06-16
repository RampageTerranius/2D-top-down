#pragma once
#include <SDL.h>

#include "Texture.h"
#include "Vector2D.h"
#include "Weapon.h"

// Entity class is relative to map.
// Being at corodinate 20,20 means your at 20,20 on the map, not the screen.
class Entity
{
public:
	Entity();

	virtual bool Render();
	void MoveCameraToHere();
	virtual void MoveBy(float x, float y);
	virtual void MoveTo(int x, int y);
	virtual void CalculateDirectionFacing();

	Vector2D location = Vector2D{ 0, 0 };
	Vector2D target = { 0, 0 };
	float directionFacing;
	int ID;
	Texture* texture;
};

class Player : public Entity
{
public:
	Player();

	void MoveBy(float x, float y);
	void CalculateDirectionFacing();
	void HandleEvents();

	void FireWeapon();
	void ReloadWeapon();
	void Dodge();
	void RenderAimer();
	void DrawUIForThisPlayer();
	void AddWeapon(Weapon* wep);
	void RemoveWeapon(int weaponIndex);
	void SwitchToNextWeapon();
	void SwitchToLastWeapon();	

	std::string name;

	int health;

	float currentRecoil;
	bool firedThisTick;
	bool firedLastTick;
	bool dodgedThisTick;
	bool dodgedLastTick;
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