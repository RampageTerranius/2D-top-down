#include "Entity.h"

#include "Globals.h"
#include "Math functions.h"

// Render the current entity to its given location.
bool Entity::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		// TODO: This does not reference where the entity exists, should be updated to reference that instead of middle of screen.
		rect.x = (int)round((windowWidth / 2) - (rect.w / 2));
		rect.y = (int)round((windowHeight / 2) - (rect.h / 2));

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
	else if (xLoc >= (float)map.GetSizeX())
		xLoc = (float)map.GetSizeX() - 1;

	if (yLoc <= 0)
		yLoc = 0;
	if (yLoc >= (float)map.GetSizeY())
		yLoc = (float)(map.GetSizeY() - 1);
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

	if (xLoc < 0)
		xLoc = 0;

	if (yLoc < 0)
		yLoc = 0;

	if (xLoc >= map.GetSizeX())
		xLoc = map.GetSizeX() - 1;

	if (yLoc >= map.GetSizeY())
		yLoc = map.GetSizeY() - 1;
}

bool Object::Render()
{
	if (map.GetSizeX() != 0 && map.GetSizeY() != 0)
	{
		if (texture != nullptr)
		{
			SDL_Rect dstRect;
			SDL_Rect srcRect = { 0, 0, 0, 0 };

			srcRect.w = texture->Rect().w;
			srcRect.h = texture->Rect().h;

			dstRect.w = texture->Rect().w;
			dstRect.h = texture->Rect().h;
			SDL_Point p;
			p.x = xLoc;
			p.y = yLoc;
			
			SDL_Point p2 = GetScreenCoordFromMapPoint(p);

			if ((p2.x >= 0 && p2.x <= windowWidth) && (p2.y >= 0 && p2.y <= windowHeight))
			{
				dstRect.x = p2.x - (dstRect.w / 2);
				dstRect.y = p2.y - (dstRect.h / 2);

				if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), &srcRect, &dstRect, NULL, NULL, SDL_FLIP_NONE) >= 0)
					return true;
			}
			else			
				return true;
		}
	}

	return false;
}