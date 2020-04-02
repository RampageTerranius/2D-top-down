#include "Render.h"

#include "Projectile.h"
#include "UI.h"
#include "Mouse.h"
#include "Globals.h"

#include <math.h>

void Render()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	SDL_RenderClear(mainRenderer);

	// Render all players.
	allPlayers.RenderAllPlayers();
	// Render all projectiles.
	allProjectiles.RenderAllProjectiles();

	testPlayer->RenderAimer();	

	// Render the ammo count.
	if (testPlayer->reloadTimer == 0)
		ttfAmmo.SetText(mainRenderer, std::to_string(testPlayer->ammoLeft));
	else
		ttfAmmo.SetText(mainRenderer, "Reloading");

	ttfAmmo.Draw(mainRenderer, 5, windowHeight - 25);

	// Render the weapon name.
	if (testPlayer->weapon != nullptr)
		ttfWeapon.SetText(mainRenderer, testPlayer->weapon->name);

	ttfWeapon.Draw(mainRenderer, 5, windowHeight - 50);
	
	SDL_RenderPresent(mainRenderer);
}