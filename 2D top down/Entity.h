#pragma once
#include <SDL.h>

#include "Texture.h"
#include "Vector2D.h"

// Entity is non-relative to the map.
// this means that setting something to 200/200 will make it exist at 200/200 on the SCREEN.
// Entities are not affected by other entities/objects when moving.
class Entity
{
public:
	Entity();

	virtual bool Render();
	virtual void MoveBy(float x, float y);
	virtual void MoveTo(int x, int y);

	Vector2D loc = Vector2D{ 0, 0 };;

	int ID;
	Texture* texture;
};

// Object is relative to the map.
// this means that setting something to 200/200 will make it exist at 200/200 on the MAP but potentially elsewhere on the SCREEN.
// Objects are affected by other objects when moving.
class Object : public Entity
{
public:
	Object();

	virtual bool Render();

	float velocity;
};
