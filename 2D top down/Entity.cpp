#include "Entity.h"

#include "Globals.h"
#include "Math functions.h"

Entity::Entity()
{
	xLoc = 0.0;
	yLoc = 0.0;

	ID = 0;
	texture = nullptr;
}

// Render the current entity to its given location.
bool Entity::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		// TODO: This does not reference where the entity exists, should be updated to reference that instead of middle of screen.
		rect.x = static_cast<int> (round((windowWidth / 2) - (rect.w / 2)));
		rect.y = static_cast<int> (round((windowHeight / 2) - (rect.h / 2)));

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, NULL, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

// Move the entity from its point of origin by the given X/Y.
void Entity::MoveBy(float x, float y)
{
	xLoc += x;
	yLoc += y;

	if (xLoc <= 0)
		xLoc = 0;
	else if (xLoc >= static_cast<float> (map.GetSizeX()))
		xLoc = static_cast<float> (map.GetSizeX() - 1);

	if (yLoc <= 0)
		yLoc = 0;
	if (yLoc >= static_cast<float> (map.GetSizeY()))
		yLoc = static_cast<float> (map.GetSizeY() - 1);
}

// Move the entity DIRECTLY to the given X/Y coords
void Entity::MoveTo(int x, int y)
{
	xLoc = static_cast<float> (x);
	yLoc = static_cast<float> (y);

	if (xLoc <= 0)
		xLoc = 0;
	else if (xLoc > static_cast<float> (windowWidth))
		xLoc = static_cast<float> (windowWidth - 1);

	if (yLoc <= 0)
		yLoc = 0;
	if (yLoc > static_cast<float> (windowHeight))
		yLoc = static_cast<float> (windowHeight - 1);
}

Object::Object()
{
	this->velocity = 0.0;
	this->directionFacing = 0.0;
}

// Automatically move the object according to its velocity and facing direction
// The objects hold their direction as an angle, not as radian so we need to convert it back.
// Returns true if has hit soemthing.
bool Object::MoveAccoringToVel()
{
	float i = static_cast<float> (cos(directionFacing * M_PI / 180) * velocity);
	float n = static_cast<float> (sin(directionFacing * M_PI / 180) * velocity);

	xLoc += i;
	yLoc += n;

	if (xLoc < 0)
	{
		xLoc = 0;
		return true;
	}

	if (yLoc < 0)
	{
		yLoc = 0;
		return true;
	}

	if (xLoc >= map.GetSizeX())
	{
		xLoc = static_cast<float> (map.GetSizeX() - 1);
		return true;
	}

	if (yLoc >= map.GetSizeY())
	{		
		yLoc = static_cast<float> (map.GetSizeY() - 1);
		return true;
	}

	return false;
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
			p.x = static_cast<int> (xLoc);
			p.y = static_cast<int> (yLoc);
			
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