#pragma once

#include "Texture.h"

#include "Entity.h"

class UI : public Entity
{
public:
	bool Render(int rotationAngle);

	int xRotLoc = -1;
	int yRotLoc = -1;
};
