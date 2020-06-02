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

	// Render the ammo count.
	if (currentPlayer->weapon.size() <= 0)
		ttfAmmo.SetText(mainRenderer, "Ammo: 0");
	else if (currentPlayer->reloadTimer == 0)
		ttfAmmo.SetText(mainRenderer, "Ammo: " + std::to_string(currentPlayer->ammoLeft[currentPlayer->selectedWeapon]));
	else
		ttfAmmo.SetText(mainRenderer, "Ammo: " + std::to_string(currentPlayer->ammoLeft[currentPlayer->selectedWeapon]) + " Reloading");

	ttfAmmo.Draw(mainRenderer, 5, windowHeight - 25);

	// Render the weapon name.
	if (currentPlayer->weapon.size() > 0)
		ttfWeapon.SetText(mainRenderer, "Weapon: " + currentPlayer->weapon[currentPlayer->selectedWeapon]->name);
	else
		ttfWeapon.SetText(mainRenderer, "Weapon: Unarmed");

	ttfWeapon.Draw(mainRenderer, 5, windowHeight - 50);

	// Render the dodges count.
	ttfDodges.SetText(mainRenderer, "Dodges: " + std::to_string(currentPlayer->dodgesLeft));

	ttfDodges.Draw(mainRenderer, 5, windowHeight - 75);
	
	SDL_RenderPresent(mainRenderer);
}