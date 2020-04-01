#include "Render.h"

#include "Projectile.h"
#include "UI.h"
#include "Mouse.h"
#include "Globals.h"

void Render()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	SDL_RenderClear(mainRenderer);

	// Render all players.
	allPlayers.RenderAllPlayers();
	// Render all projectiles.
	allProjectiles.RenderAllProjectiles();
	
	// Render the test players aimer.
	UI aimer = UI();

	aimer.texture = allTextures.GetTexture("AimMarker");

	aimer.xLoc = mouse.x + ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2);
	aimer.yLoc = mouse.y;
	aimer.Render(90);

	aimer.xLoc = mouse.x - ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2);
	aimer.yLoc = mouse.y;
	aimer.Render(270);

	aimer.xLoc = mouse.x;
	aimer.yLoc = mouse.y - ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2);
	aimer.Render(0);

	aimer.xLoc = mouse.x;
	aimer.yLoc = mouse.y + ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2);
	aimer.Render(180);

	// Render the ammo count.
	if (testPlayer->reloadTimer == 0)
		ttfAmmo.SetText(mainRenderer, std::to_string(testPlayer->ammoLeft));
	else
		ttfAmmo.SetText(mainRenderer, "Reloading");
	ttfAmmo.Draw(mainRenderer, 5, windowHeight - 25);
	
	SDL_RenderPresent(mainRenderer);
}