#pragma once

#include "Entity.h"
#include "Weapon.h"

class Character : public Entity
{
public:
	double directionFacing;
	bool Render();
};

class Player : public Character
{
public:
	int health;
	Weapon weapon;

	int xVel;// -1 = left 0 = none 1 = right
	int yVel;// -1 = up 0 = none 1 = down
	
	int walkVel = 2;
	int sprintVel = 5;

	bool sprinting;
	
	float velDropWhenOverMaxVel;

	void MovePlayerAccordingToInput();	
};