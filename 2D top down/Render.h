#pragma once

#include "Globals.h"

void Render()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	SDL_RenderClear(mainRenderer);

	pl.Render();

	SDL_RenderPresent(mainRenderer);

	SDL_Delay(100);
}