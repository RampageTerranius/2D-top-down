#include "Render.h"

#include "Projectile.h"
#include "UI.h"
#include "Globals.h"

#include <math.h>

void Render()
{
	SDL_RenderClear(mainRenderer);

	//Render the map to the screen.
	map.Render();

	// Render all players.
	allPlayers.RenderAllPlayers();
	// Render all projectiles.
	allProjectiles.RenderAllProjectiles();

	currentPlayer->RenderAimer();
	currentPlayer->DrawUIForThisPlayer();

	ttfFPS.SetText((std::to_string(static_cast<int> (round(avgFPS)))));
	ttfFPS.Draw();
	
	SDL_RenderPresent(mainRenderer);
}