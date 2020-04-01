#include "Render.h"

#include "Projectile.h"
#include "Globals.h"

void Render()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	SDL_RenderClear(mainRenderer);

	allPlayers.RenderAllPlayers();
	allProjectiles.RenderAllProjectiles();

	SDL_RenderPresent(mainRenderer);
}