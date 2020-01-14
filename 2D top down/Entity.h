#pragma once
#include <SDL.h>

#include "Texture.h"

class Entity
{
public:
	SDL_Point point;
	int ID;

	Texture* texture;
};

class Player : public Entity
{
public:
	double dir;
};