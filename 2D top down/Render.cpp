#include "Render.h"

#include "Projectile.h"

void Render()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	SDL_RenderClear(mainRenderer);

	pl.Render();
	allProjectiles.RenderAllProjectiles();

	SDL_RenderPresent(mainRenderer);
}