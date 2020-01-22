#include "Entity.h"

#include "Globals.h"

// Render the current entity to its given location.
bool Entity::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.x = point.x;
		rect.y = point.y;
		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		rect.x -= (rect.w / 2);
		rect.y -= (rect.h / 2);

		if (SDL_RenderCopyEx(mainRenderer, pl.texture->Tex(), NULL, &rect, pl.directionFacing, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

// Move the entity from its point of origin by the given X/Y.
void Entity::MoveObjectBy(int x, int y)
{
	point.x += x;
	point.y += y;

	if (point.x <= 0)
		point.x = 0;

	if (point.y > windowHeight)
		point.y = windowHeight - 1;
}

// Move the entity DIRECTLY to the given X/Y coords
void Entity::MoveObjectTo(int x, int y)
{
	point.x = x;
	point.y = y;

	if (point.x <= 0)
		point.x = 0;

	if (point.y > windowHeight)
		point.y = windowHeight - 1;
}

// Automatically move the object according to its velocity and facing direction
// The entities hold their direction as an angle, not as radian so we need to convert it back.
void Object::MoveObjectAccoringToVel()
{
	point.x += cos(directionFacing * M_PI / 180) * velocity;
	point.y += sin(directionFacing * M_PI / 180) * velocity;

	if (point.x <= 0)
		point.x = 0;

	if (point.y > windowHeight)
		point.y = windowHeight - 1;
}