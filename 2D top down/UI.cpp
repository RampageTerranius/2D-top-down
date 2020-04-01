#include "UI.h"

#include "Globals.h"

bool UI::Render(int rotationAngle)
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.x = (int)std::round(xLoc);
		rect.y = (int)std::round(yLoc);
		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		rect.x -= (rect.w / 2);
		rect.y -= (rect.h / 2);

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, rotationAngle, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render a UI object");

	return false;
}