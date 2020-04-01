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

	if (allTextures.GetTexture("DirMarker") == nullptr || allTextures.GetTexture("Bullet") == nullptr)
	{
		debug.Log("Setup+Shutdown", "Setup", "failed to load textures");
		return false;
	}



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
	wep->recoilControlRate = 15;
	wep->totalAmmo = 30;
	wep->fireType = FIRETYPE_FULLAUTO;
	// TODO

	allWeapons.AddWeapon(wep);

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