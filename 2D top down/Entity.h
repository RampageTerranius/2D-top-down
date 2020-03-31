#pragma once
#include <SDL.h>

#include "Texture.h"

class Entity
{
public:
	virtual bool Render();
	void MoveObjectBy(int x, int y);
	void MoveObjectTo(int x, int y);

	double xLoc;
	double yLoc;
	int ID;
	Texture* texture;
};

class Object : public Entity
{
public:
	void MoveObjectAccoringToVel();

	double velocity;
	double directionFacing;
};