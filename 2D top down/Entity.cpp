#include "Entity.h"

#include "Globals.h"

// Render the current entity to its given location.
bool Entity::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.x = (int)round(xLoc);
		rect.y = (int)round(yLoc);
		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		rect.x -= (int)round((float)rect.w / 2);
		rect.y -= (int)round((float)rect.h / 2);

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, NULL, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

// Move the entity from its point of origin by the given X/Y.
void Entity::MoveObjectBy(float x, float y)
{
	xLoc += x;
	yLoc += y;

	if (xLoc <= 0)
		xLoc = 0;
	else if (xLoc > (float)windowWidth)
		xLoc = (float)windowWidth - 1;

	if (yLoc <= 0)
		yLoc = 0;
	if (yLoc > (float)windowHeight)
		yLoc = (float)(windowHeight - 1);
}

// Move the entity DIRECTLY to the given X/Y coords
void Entity::MoveObjectTo(int x, int y)
{
	xLoc = (float)x;
	yLoc = (float)y;

	if (xLoc <= 0)
		xLoc = 0;
	else if (xLoc > (float)windowWidth)
		xLoc = (float)windowWidth - 1;

	if (yLoc <= 0)
		yLoc = 0;
	if (yLoc > (float)windowHeight)
		yLoc = (float)(windowHeight - 1);
}

// Automatically move the object according to its velocity and facing direction
// The objects hold their direction as an angle, not as radian so we need to convert it back.
void Object::MoveObjectAccoringToVel()
{
	float i = (float)(cos(directionFacing * M_PI / 180) * velocity);
	float n = (float)(sin(directionFacing * M_PI / 180) * velocity);

	xLoc += i;
	yLoc += n;

	if (xLoc <= 0)
		xLoc = 0;

	if ((int)round(yLoc) > windowHeight)
		yLoc = (float)(windowHeight - 1);
}