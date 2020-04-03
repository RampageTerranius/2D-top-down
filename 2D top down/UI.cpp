#include "UI.h"

#include "Globals.h"

bool UI::Render(int rotationAngle)
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

		if (xRotLoc < 0 || yRotLoc < 0)
		{
			if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, rotationAngle, NULL, SDL_FLIP_NONE) >= 0)
				return true;
		}
		else
		{
			SDL_Point rotpoint;
			rotpoint.x = xRotLoc;
			rotpoint.y = yRotLoc;
			if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, rotationAngle, &rotpoint, SDL_FLIP_NONE) >= 0)
				return true;
		}
	}

	debug.Log("Entity", "Render", "failed to render a UI object");

	return false;
}