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

	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	debug.Log("Setup+Shutdown", "Setup", "Loading textures...");	

	allTextures.CreateTexture(GetEXEPath() + "\\Direction Marker.png", "DirMarker");
	allTextures.CreateTexture(GetEXEPath() + "\\Bullet.png", "Bullet");
	allTextures.CreateTexture(GetEXEPath() + "\\Aim Marker Top.png", "AimMarkerTop");
	allTextures.CreateTexture(GetEXEPath() + "\\Aim Marker Bottom.png", "AimMarkerBottom");
	allTextures.CreateTexture(GetEXEPath() + "\\Aim Marker Left.png", "AimMarkerLeft");
	allTextures.CreateTexture(GetEXEPath() + "\\Aim Marker Right.png", "AimMarkerRight");
	allTextures.CreateTexture(GetEXEPath() + "\\Red Dot.png", "RedDot");

	if (allTextures.GetTexture("DirMarker") == nullptr || allTextures.GetTexture("Bullet") == nullptr || allTextures.GetTexture("AimMarkerTop") == nullptr || allTextures.GetTexture("AimMarkerBottom") == nullptr || allTextures.GetTexture("AimMarkerLeft") == nullptr || allTextures.GetTexture("AimMarkerRight") == nullptr || allTextures.GetTexture("RedDot") == nullptr)
	{
		debug.Log("Setup+Shutdown", "Setup", "failed to load textures");
		return false;
	}

	if (!ttfWeapon.SetFont(GetEXEPath() + "\\pxl.ttf", 20) || !ttfAmmo.SetFont(GetEXEPath() + "\\pxl.ttf", 20) || !ttfFPS.SetFont(GetEXEPath() + "\\pxl.ttf", 20) || !ttfDodges.SetFont(GetEXEPath() + "\\pxl.ttf", 20))
	{
		debug.Log("Setup+Shutdown", "Setup", "failed to load fonts");
		return false;
	}

	ttfFPS.SetColor(255, 255, 0);
	ttfAmmo.SetColor(255, 255, 0);
	ttfWeapon.SetColor(255, 255, 0);
	ttfDodges.SetColor(255, 255, 0);

	// TODO: weapon array etc.
	Weapon* wep = new Weapon;
	wep->damage = 5;
	wep->name = "Smg";
	wep->projectileDistance = 500;
	wep->projectileSpeed = 20;
	wep->fireRate = 6;
	wep->reloadTime = 90;
	wep->deviation = 30;
	wep->maxDeviation = 80;
	wep->recoil = 8;
	wep->recoilControlRate = 6;
	wep->totalAmmo = 30;
	wep->fireType = FIRETYPE_FULLAUTO;
	wep->reloadType = RELOADTYPE_CLIP;
	allWeapons.AddWeapon(wep);

	Weapon* wep2 = new Weapon;
	wep2->damage = 20;
	wep2->name = "Battle Rifle";
	wep2->projectileDistance = 1000;
	wep2->projectileSpeed = 50;
	wep2->fireRate = 15;
	wep2->reloadTime = 110;
	wep2->deviation = 10;
	wep2->maxDeviation = 120;
	wep2->recoil = 40;
	wep2->recoilControlRate = 5;
	wep2->totalAmmo = 20;
	wep2->fireType = FIRETYPE_FULLAUTO;
	wep2->reloadType = RELOADTYPE_CLIP;
	allWeapons.AddWeapon(wep2);

	Weapon* wep3 = new Weapon;
	wep3->damage = 4;
	wep3->name = "Lmg";
	wep3->projectileDistance = 400;
	wep3->projectileSpeed = 30;
	wep3->fireRate = 3;
	wep3->reloadTime = 180;
	wep3->deviation = 30;
	wep3->maxDeviation = 160;
	wep3->recoil = 13;
	wep3->recoilControlRate = 4;
	wep3->totalAmmo = 100;
	wep3->fireType = FIRETYPE_FULLAUTO;
	wep3->reloadType = RELOADTYPE_CLIP;
	allWeapons.AddWeapon(wep3);

	Weapon* wep4 = new Weapon;
	wep4->damage = 80;
	wep4->name = "Bolt Rifle";
	wep4->projectileDistance = 1000;
	wep4->projectileSpeed = 100;
	wep4->fireRate = 60;
	wep4->reloadTime = 200;
	wep4->deviation = 5;
	wep4->maxDeviation = 120;
	wep4->recoil = 60;
	wep4->recoilControlRate = 5;
	wep4->totalAmmo = 5;
	wep4->fireType = FIRETYPE_SEMIAUTO;
	wep4->reloadType = RELOADTYPE_CLIP;
	allWeapons.AddWeapon(wep4);

	Weapon* wep5 = new Weapon;
	wep5->damage = 50;
	wep5->name = "Test - No speed";
	wep5->projectileDistance = 100;
	wep5->projectileSpeed = 0;
	wep5->fireRate = 30;
	wep5->reloadTime = 1;
	wep5->deviation = 1;
	wep5->maxDeviation = 1;
	wep5->recoil = 1;
	wep5->recoilControlRate = 1;
	wep5->totalAmmo = 30;
	wep5->fireType = FIRETYPE_FULLAUTO;
	wep5->reloadType = RELOADTYPE_CLIP;
	allWeapons.AddWeapon(wep5);

	Weapon* wep6 = new Weapon;
	wep6->damage = 9999999;
	wep6->name = "Test - Wall Breaker";
	wep6->projectileDistance = 1000;
	wep6->projectileSpeed = 10;
	wep6->fireRate = 30;
	wep6->reloadTime = 1;
	wep6->deviation = 1;
	wep6->maxDeviation = 1;
	wep6->recoil = 1;
	wep6->recoilControlRate = 1;
	wep6->totalAmmo = 30;
	wep6->fireType = FIRETYPE_FULLAUTO;
	wep6->reloadType = RELOADTYPE_CLIP;
	allWeapons.AddWeapon(wep6);

	Weapon* wep7 = new Weapon;
	wep7->damage = 5;
	wep7->name = "Shotgun";
	wep7->projectileDistance = 200;
	wep7->projectileSpeed = 5;
	wep7->fireRate = 40;
	wep7->reloadTime = 30;
	wep7->deviation = 60;
	wep7->maxDeviation = 220;
	wep7->recoil = 100;
	wep7->recoilControlRate = 2;
	wep7->bulletsPerShot = 12;
	wep7->totalAmmo = 7;
	wep7->fireType = FIRETYPE_SEMIAUTO;
	wep7->reloadType = RELOADTYPE_SINGLE;
	allWeapons.AddWeapon(wep7);
	// TODO	

	testPlayer = allPlayers.CreatePlayer("TestPlayer");
	testPlayer->texture = allTextures.GetTexture("DirMarker");
	//testPlayer->xLoc = round(static_cast<float> (windowWidth / 2));
	//testPlayer->yLoc = round(static_cast<float> (windowHeight / 2));
	testPlayer->xLoc = 499;
	testPlayer->yLoc = 499;
	testPlayer->weapon = allWeapons.GetWeapon("Test - No speed");

	debug.Log("Setup+Shutdown", "Setup", "Setup completed");

	if (HardwareCursor)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);

	for (int i = 0; i < map.GetSizeX(); i++)
		for (int n = 0; n < map.GetSizeY(); n++)
			if ((n == 0 || n == map.GetSizeY() - 1) || (i == 0 || i == map.GetSizeX() - 1))
				map.SetDataAt(i, n, MAPDATATYPE_WALL, baseWallHealth);

	map.SetDataAt(499, 500, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(499, 499, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(500, 500, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(500, 499, MAPDATATYPE_WALL, baseWallHealth);

	// Map test data.
	map.SetDataAt(50, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(51, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(52, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(53, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(54, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(55, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(56, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(57, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(58, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(59, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(60, 100, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(61, 100, MAPDATATYPE_WALL, baseWallHealth);

	map.SetDataAt(51, 99, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(51, 101, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(52, 98, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(52, 102, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(53, 97, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(53, 103, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(54, 96, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(54, 104, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(55, 95, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(55, 105, MAPDATATYPE_WALL, baseWallHealth);

	map.SetDataAt(100, 50, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 51, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 52, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 53, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 54, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 55, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 56, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 57, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 58, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 59, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 60, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(100, 61, MAPDATATYPE_WALL, baseWallHealth);

	map.SetDataAt(99, 51, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(101, 51, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(98, 52, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(102, 52, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(97, 53, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(103, 53, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(96, 54, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(104, 54, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(95, 55, MAPDATATYPE_WALL, baseWallHealth);
	map.SetDataAt(105, 55, MAPDATATYPE_WALL, baseWallHealth);

	for (int i = map.GetSizeX() - 200; i <= map.GetSizeX() - 100; i++)
		for (int n = 100; n <= map.GetSizeY() - 100; n++)
			map.SetDataAt(i, n, MAPDATATYPE_WALL, baseWallHealth);

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

	allWeapons.RemoveAllWeapons();
	allPlayers.DeleteAllPlayers();
	allProjectiles.DestroyAllProjectiles();	
	allTextures.Cleanup();

	debug.Log("Setup+Shutdown", "Shutdown", "Shutdown completed");
}