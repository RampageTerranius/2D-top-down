#pragma once

#include "Globals.h"

void Render()
{
	SDL_Rect rect;
	rect.x = pl.point.x;
	rect.y = pl.point.y;
	rect.w = pl.texture->W();
	rect.h = pl.texture->H();

	SDL_RenderCopyEx(mainRenderer, pl.texture->Tex(), NULL, &rect, pl.dir, NULL, SDL_FLIP_NONE);
}