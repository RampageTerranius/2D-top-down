#pragma once
#include <SDL.h>

#include "Texture.h"

class Entity
{
public:
	bool Render();
	void MoveObjectBy(int x, int y);
	void MoveObjectTo(int x, int y);

	SDL_Point point;
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


























class Player : public Object
{
public:
};

