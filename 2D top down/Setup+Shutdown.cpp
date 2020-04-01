#include "Setup+Shutdown.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <ctime>

#include "Globals.h"
#include "Texture.h"
#include "MiscFunctions.h"

// Setup the engine, preparing everything required.
bool SetupEngine()
{
	debug.showMessagesOnConsole = true;

	debug.Log("Setup+Shutdown", "Setup", "Starting setup...");

	debug.Log("Setup+Shutdown", "Setup", "Initializing SDL sub-routines...");

	srand(static_cast <unsigned> (time(0)));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::string str = SDL_GetError();
		debug.Log("Setup+Shutdown", "Setup", "SDL failed to initialize" + str);
		return false;
	}

	debug.Log("Setup+Shutdown", "Setup", "Initializing SDL_TTF sub-routines...");

	if (TTF_Init() != 0)
	{
		std::string str = SDL_GetError();

		debug.Log("Setup+Shutdown", "Setup", "TTF failed to initialize" + str);
		return false;
	}
	
	debug.Log("Setup+Shutdown", "Setup", "Preparing SDL renderer and creating main window...");

	// Create main window.
	const int WINDOW_WIDTH = windowWidth;
	const int WINDOW_HEIGHT = windowHeight;

	Uint32 windowFlags = SDL_WINDOW_OPENGL;
	mainWindow = SDL_CreateWindow(programName.c_str(), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

	mainSurface = SDL_GetWindowSurface(mainWindow);

	Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, renderFlags);	

	debug.Log("Setup+Shutdown", "Setup", "Loading textures...");	

	allTextures.CreateTexture(GetEXEPath() + "\\Direction Marker.png", "DirMarker");
	allTextures.CreateTexture(GetEXEPath() + "\\Bullet.png", "Bullet");
	allTextures.CreateTexture(GetEXEPath() + "\\Aim Marker.png", "AimMarker");

	if (allTextures.GetTexture("DirMarker") == nullptr || allTextures.GetTexture("Bullet") == nullptr || allTextures.GetTexture("AimMarker") == nullptr)
	{
		debug.Log("Setup+Shutdown", "Setup", "failed to load textures");
		return false;
	}

	if (!ttfFPS.SetFont(GetEXEPath() + "\\pxl.ttf", 20) || !ttfAmmo.SetFont(GetEXEPath() + "\\pxl.ttf", 20))
	{
		debug.Log("Setup+Shutdown", "Setup", "failed to load fonts");
		return false;
	}

	ttfFPS.SetColor(255, 255, 0);
	ttfAmmo.SetColor(255, 255, 0);

	// TODO: weapon array etc.
	Weapon* wep = new Weapon;

	wep->damage = 5;
	wep->name = "Smg";
	wep->projectileDistance = 500;
	wep->projectileSpeed = 20;
	wep->fireRate = 6;
	wep->reloadTime = 30;
	wep->deviation = 30;
	wep->maxDeviation = 80;
	wep->recoil = 8;
	wep->recoilControlRate = 6;
	wep->totalAmmo = 30;
	wep->fireType = FIRETYPE_FULLAUTO;
	allWeapons.AddWeapon(wep);

	Weapon* wep2 = new Weapon;

	wep2->damage = 20;
	wep2->name = "Battle Rifle";
	wep2->projectileDistance = 1000;
	wep2->projectileSpeed = 30;
	wep2->fireRate = 15;
	wep2->reloadTime = 30;
	wep2->deviation = 5;
	wep2->maxDeviation = 120;
	wep2->recoil = 40;
	wep2->recoilControlRate = 5;
	wep2->totalAmmo = 20;
	wep2->fireType = FIRETYPE_FULLAUTO;
	allWeapons.AddWeapon(wep2);
	// TODO

	

	testPlayer = allPlayers.CreatePlayer("TestPlayer");
	testPlayer->texture = allTextures.GetTexture("DirMarker");
	testPlayer->xLoc = (windowWidth / 2) - (testPlayer->texture->Rect().w / 2);
	testPlayer->yLoc = (windowHeight / 2) - (testPlayer->texture->Rect().h / 2);
	testPlayer->weapon = allWeapons.GetWeapon("Smg");	 

	debug.Log("Setup+Shutdown", "Setup", "Setup completed");

	return true;
}

// Shutdown the engine, cleaning up everything as required.
void ShutdownEngine()
{
	debug.Log("Setup+Shutdown", "Shutdown", "Shutting down engine...");
	   
	SDL_Quit();

	// Destroy the main renderer before shutdown.
	if (mainRenderer != nullptr)
		SDL_DestroyRenderer(mainRenderer);

	// Destroy the main window before shutdown.
	if (mainWindow != nullptr)
		SDL_DestroyWindow(mainWindow);

	// Destroy the surface used for drawing particles.
	if (mainSurface != nullptr)
		SDL_FreeSurface(mainSurface);

	debug.Log("Setup+Shutdown", "Shutdown", "Shutdown completed");
}