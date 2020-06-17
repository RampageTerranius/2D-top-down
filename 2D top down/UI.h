#pragma once

#include "Texture.h"

#include "Entity.h"

// UI class is relative to the screen.
// This class is best used for objects that need to be at a specific coordinate on the screen reguardless of map.

class UI : public Entity
{
public:
	bool Render(int rotationAngle);
};
