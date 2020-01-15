#include "Entity.h"

#include "Globals.h"

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

		if (SDL_RenderCopyEx(mainRenderer, pl.texture->Tex(), NULL, &rect, pl.dir, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}