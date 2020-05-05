#include "Render.h"

#include "Projectile.h"
#include "UI.h"
#include "Mouse.h"
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

	testPlayer->RenderAimer();

	// Render the ammo count.
	if (testPlayer->reloadTimer == 0)
		ttfAmmo.SetText(mainRenderer, "Ammo: " + std::to_string(testPlayer->ammoLeft));
	else
		ttfAmmo.SetText(mainRenderer, "Reloading");

	ttfAmmo.Draw(mainRenderer, 5, windowHeight - 25);

	// Render the weapon name.
	if (testPlayer->weapon != nullptr)
		ttfWeapon.SetText(mainRenderer, "Weapon: " + testPlayer->weapon->name);

	ttfWeapon.Draw(mainRenderer, 5, windowHeight - 50);

	// Render the dodges count.
	ttfDodges.SetText(mainRenderer, "Dodges: " + std::to_string(testPlayer->dodgesLeft));

	ttfDodges.Draw(mainRenderer, 5, windowHeight - 75);
	
	SDL_RenderPresent(mainRenderer);
}