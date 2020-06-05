#include "Entity.h"

#include "Globals.h"
#include "Math functions.h"
#include "Vector2D.h"

Entity::Entity()
{
	this->ID = 0;
	this->texture = nullptr;
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
		rect.x = static_cast<int> (round(windowWidthDiv2 - (rect.w / 2)));
		rect.y = static_cast<int> (round(windowHeightDiv2 - (rect.h / 2)));

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, NULL, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

// Move the entity from its point of origin by the given X/Y.
void Entity::MoveBy(float x, float y)
{
	this->loc.x += x;
	this->loc.y += y;

	if (this->loc.x <= 0)
		this->loc.x = 0;
	else if (this->loc.x >= static_cast<float> (map.GetSizeX()))
		this->loc.x = static_cast<float> (map.GetSizeX() - 1);

	if (this->loc.y <= 0)
		this->loc.y = 0;
	if (this->loc.y >= static_cast<float> (map.GetSizeY()))
		this->loc.y = static_cast<float> (map.GetSizeY() - 1);
}

// Move the entity DIRECTLY to the given X/Y coords
void Entity::MoveTo(int x, int y)
{
	this->loc.x = static_cast<float> (x);
	this->loc.y = static_cast<float> (y);

	if (this->loc.x <= 0)
		this->loc.x = 0;
	else if (this->loc.x >= static_cast<float> (map.GetSizeX()))
		this->loc.x = static_cast<float> (map.GetSizeX() - 1);

	if (this->loc.y <= 0)
		this->loc.y = 0;
	if (this->loc.y >= static_cast<float> (map.GetSizeY()))
		this->loc.y = static_cast<float> (map.GetSizeY() - 1);
}

Object::Object()
{
	this->velocity = 0.0f;
	this->ID = 0;
	this->loc = Vector2D(0, 0);
	this->texture = nullptr;
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
			p.x = static_cast<int> (this->loc.x);
			p.y = static_cast<int> (this->loc.y);
			
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