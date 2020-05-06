#pragma once
#include <SDL.h>

#include "Texture.h"

// Entity is non-relative to the map.
// this means that setting something to 200/200 will make it exist at 200/200 on the SCREEN.
class Entity
{
public:
	virtual bool Render();
	void MoveObjectBy(float x, float y);
	void MoveObjectTo(int x, int y);

	float xLoc;
	float yLoc;
	int ID;
	Texture* texture;
};

// Object is relative to the map.
// this means that setting something to 200/200 will make it exist at 200/200 on the MAP but potentially elsewhere on the SCREEN.
class Object : public Entity
{
public:
	void MoveObjectAccoringToVel();
	virtual bool Render();

	float velocity;
	float directionFacing;
};