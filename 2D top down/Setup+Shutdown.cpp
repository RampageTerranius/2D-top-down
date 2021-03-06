#include "Setup+Shutdown.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "simpleini-4.17/SimpleIni.h"

#include "Globals.h"
#include "Texture.h"
#include "MiscFunctions.h"
#include "Debug.h"

// Setup the engine, preparing everything required.
bool SetupEngine()
{
	debug.showMessagesOnConsole = true;

	debug.Log("Setup+Shutdown", "SetupEngine", "Starting setup...");

	debug.Log("Setup+Shutdown", "SetupEngine", "Initializing SDL sub-routines...");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::string str = SDL_GetError();
		debug.Log("Setup+Shutdown", "SetupEngine", "SDL failed to initialize | " + str);
		return false;
	}

	debug.Log("Setup+Shutdown", "SetupEngine", "Initializing SDL_TTF sub-routines...");

	if (TTF_Init() != 0)
	{
		std::string str = SDL_GetError();

		debug.Log("Setup+Shutdown", "SetupEngine", "TTF failed to initialize | " + str);
		return false;
	}

	debug.Log("Setup+Shutdown", "SetupEngine", "Initializing SDL_MIXER sub-routines...");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::string str = Mix_GetError();

		debug.Log("Setup+Shutdown", "SetupEngine", "Mixer failed to initialize | " + str);
		return false;
	}

	Mix_AllocateChannels(32);

	// Load the audio files into memory
	debug.Log("Setup+Shutdown", "SetupEngine", "Loading audio files...");

	if (allSounds.CreateSound(GetEXEPath() + "\\Sound\\Rifle Fire.aiff", "Rifle Fire", true) == nullptr)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load Rifle firing sound...");
		return false;
	}

	if (allSounds.CreateSound(GetEXEPath() + "\\Sound\\Shotgun Fire.wav", "Shotgun Fire", true) == nullptr)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load Shotgun firing sound...");
		return false;
	}

	if (allSounds.CreateSound(GetEXEPath() + "\\Sound\\Pistol Fire.wav", "Pistol Fire", true) == nullptr)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load Pistol firing sound...");
		return false;
	}

	if (allSounds.CreateSound(GetEXEPath() + "\\Sound\\Sniper Fire.wav", "Sniper Fire", true) == nullptr)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load Sniper firing sound...");
		return false;
	}

	if (allSounds.CreateSound(GetEXEPath() + "\\Sound\\Dodge.wav", "Dodge", true) == nullptr)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load Dodge sound...");
		return false;
	}


	debug.Log("Setup+Shutdown", "SetupEngine", "Loading setting file...");

	CSimpleIni ini;
	if (ini.LoadFile((GetEXEPath() + "\\settings.ini.").c_str()) < 0)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load Settings.ini.");
		return false;
	}

	debug.Log("Setup+Shutdown", "SetupEngine", "Preparing SDL renderer and creating main window...");

	{
		std::stringstream sStr;	
		int i = 0;

		// Get window settings.
		sStr << ini.GetValue("Window", "Width", "0");
		sStr >> i;
		windowWidth = i;

		debug.Log("Setup+Shutdown", "SetupEngine", "Window width set at " + std::to_string(windowWidth));

		sStr = std::stringstream();
		sStr << ini.GetValue("Window", "Height", "0");
		sStr >> i;
		windowHeight = i;

		debug.Log("Setup+Shutdown", "SetupEngine", "Window height set at " + std::to_string(windowHeight));

		const int WINDOW_WIDTH = windowWidth;
		const int WINDOW_HEIGHT = windowHeight;
		windowWidthDiv2 = windowWidth / 2;
		windowHeightDiv2 = windowHeight / 2;
		if (WINDOW_WIDTH < 640 || WINDOW_HEIGHT < 480)
		{
			debug.Log("Setup+Shutdown", "SetupEngine", "Invalid window width/height given. Window must be at least 640x480.");
			return false;
		}

		// Create main window.
		sStr = std::stringstream();
		sStr << ini.GetValue("Video", "FullScreen", "0");
		sStr >> i;

		if (i)
			debug.Log("Setup+Shutdown", "SetupEngine", "Window set to fullscreen");
		else if (!i)
			debug.Log("Setup+Shutdown", "SetupEngine", "Window set to windowed");
		else
			debug.Log("Setup+Shutdown", "SetupEngine", "Fullscreen mode given unknown parameter");

		Uint32 windowFlags = SDL_WINDOW_OPENGL;
		
		if (i == 1)
			windowFlags = SDL_WINDOW_FULLSCREEN;
		
		mainWindow = SDL_CreateWindow(programName.c_str(), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

		mainSurface = SDL_GetWindowSurface(mainWindow);

		sStr = std::stringstream();
		sStr << ini.GetValue("Video", "Framerate", "30");
		sStr >> i;
		frameRate = i;		
		
		if (i > 0)
		{
			ticksPerFrame = 1000 / frameRate;
			debug.Log("Setup+Shutdown", "SetupEngine", "Framerate set at " + std::to_string(frameRate));
		}
		else
		{
			capFrameRate = false;			
			debug.Log("Setup+Shutdown", "SetupEngine", "Framerate set to no limit");
		}

		// Get vsync settings.
		sStr = std::stringstream();
		sStr << ini.GetValue("Video", "VSync", "0");
		sStr >> i;

		if (!i)
			debug.Log("Setup+Shutdown", "SetupEngine", "Vsync set to off");
		else if (i)
			debug.Log("Setup+Shutdown", "SetupEngine", "Vsync set to on");
		else
			debug.Log("Setup+Shutdown", "SetupEngine", "Vsync mode given unknown parameter");

		Uint32 renderFlags = SDL_RENDERER_ACCELERATED;
		if (i == 1)
			renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

		mainRenderer = SDL_CreateRenderer(mainWindow, -1, renderFlags);
	}

	// Get input binds.
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Loading input binds...");
		
		CSimpleIniA::TNamesDepend keys;
		ini.GetAllKeys("Input", keys);

		for (CSimpleIniA::TNamesDepend::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string str = it->pItem;

			int i = 0;
			std::stringstream sStr;
			sStr << ini.GetValue("Input", str.c_str(), "0");
			sStr >> i;
			iManager->Bind(i, str);			
		}
	}

	SDL_SetRenderDrawColor(mainRenderer, renderColorR, renderColorG, renderColorB, renderColorA);

	debug.Log("Setup+Shutdown", "SetupEngine", "Loading textures...");	

	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Direction Marker.png", "DirMarker");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Direction Marker2.png", "DirMarker2");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Bullet.png", "Bullet");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Aim Marker Top.png", "AimMarkerTop");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Aim Marker Bottom.png", "AimMarkerBottom");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Aim Marker Left.png", "AimMarkerLeft");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Aim Marker Right.png", "AimMarkerRight");
	allTextures.CreateTexture(GetEXEPath() + "\\Images\\Red Dot.png", "RedDot");

	if (allTextures.GetTexture("DirMarker") == nullptr || allTextures.GetTexture("Bullet") == nullptr || allTextures.GetTexture("AimMarkerTop") == nullptr || allTextures.GetTexture("AimMarkerBottom") == nullptr || allTextures.GetTexture("AimMarkerLeft") == nullptr || allTextures.GetTexture("AimMarkerRight") == nullptr || allTextures.GetTexture("RedDot") == nullptr)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "failed to load textures");
		return false;
	}

	// TTF setup.
	ttfFPS = TTF(mainRenderer);
	ttfAmmo = TTF(mainRenderer);
	ttfWeapon = TTF(mainRenderer);
	ttfDodges = TTF(mainRenderer);

	if (!ttfWeapon.SetFont(GetEXEPath() + "\\Fonts\\pxl.ttf", 20) || !ttfAmmo.SetFont(GetEXEPath() + "\\Fonts\\pxl.ttf", 20) || !ttfFPS.SetFont(GetEXEPath() + "\\Fonts\\pxl.ttf", 20) || !ttfDodges.SetFont(GetEXEPath() + "\\Fonts\\pxl.ttf", 20))
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "failed to load fonts");
		return false;
	}

	ttfFPS.SetColor(255, 255, 0);
	ttfAmmo.SetColor(255, 255, 0);
	ttfWeapon.SetColor(255, 255, 0);
	ttfDodges.SetColor(255, 255, 0);
	ttfAmmo.x = 5;
	ttfAmmo.y = windowHeight - 25;
	ttfWeapon.x = 5;
	ttfWeapon.y = windowHeight - 50;
	ttfDodges.x = 5;
	ttfDodges.y = windowHeight - 75;
	ttfFPS.x = windowWidth - 25;
	ttfFPS.y = windowHeight - 25;
	

	debug.Log("Setup+Shutdown", "SetupEngine", "Loading weapon file...");

	// TODO: weapon array etc.
	ini.Reset();

	if (ini.LoadFile((GetEXEPath() + "\\weapons.ini.").c_str()) < 0)
	{
		debug.Log("Setup+Shutdown", "SetupEngine", "Failed to load weapon file.");
		return false;
	}

	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);

	for (CSimpleIniA::Entry entry : sections)
	{
		CSimpleIniA::TNamesDepend keys;
		ini.GetAllKeys(entry.pItem, keys);
		Weapon* wep = new Weapon();

		wep->name = entry.pItem;

		for (CSimpleIniA::TNamesDepend::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string str = it->pItem;

			// TODO: There HAS to be a better way of going about loading each weapons data... is there a way to somehow use strings in a switch statement?
			if (str == "damage")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->damage = i;
			} 
			else if (str == "projectileDistance")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->projectileDistance = i;
			}
			else if (str == "projectileSpeed")
			{
				float f = 0.0f;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> f;
				wep->projectileSpeed = f;
			}
			else if (str == "fireRate")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->fireRate = i;
			}
			else if (str == "reloadTime")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->reloadTime = i;
			}
			else if (str == "deviation")
			{
				float f = 0.0f;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> f;
				wep->deviation = f;
			}
			else if (str == "maxDeviation")
			{
				float f = 0.0f;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> f;
				wep->maxDeviation = f;
			}
			else if (str == "recoil")
			{
				float f = 0.0f;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> f;
				wep->recoil = f;
			}
			else if (str == "recoilControlRate")
			{
				float f = 0.0f;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> f;
				wep->recoilControlRate = f;
			}
			else if (str == "bulletsPerShot")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->bulletsPerShot = i;
			}
			else if (str == "totalAmmo")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->totalAmmo = i;
			}
			else if (str == "fireType")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->fireType = static_cast<FireType> (i);
			}
			else if (str == "reloadType")
			{
				int i = 0;
				std::stringstream sStr;
				sStr << ini.GetValue(entry.pItem, it->pItem, "0");
				sStr >> i;
				wep->reloadType = static_cast<ReloadType> (i);
			}
			else if (str == "fireSound")			
				wep->fireSound = allSounds.GetSound(ini.GetValue(entry.pItem, it->pItem, "NO SOUND"));	
			else if (str == "reloadSound")
				wep->reloadSound = allSounds.GetSound(ini.GetValue(entry.pItem, it->pItem, "NO SOUND"));
		}

		allWeapons.AddWeapon(wep);
	}

	allPlayers.CreatePlayer("Player1");
	allPlayers.CreatePlayer("Player2");

	currentPlayer = allPlayers.GetPlayer("Player1");
	currentPlayer->texture = allTextures.GetTexture("DirMarker");
	currentPlayer->location.x = round(static_cast<float> ((map.GetSizeX() - 1) / 2));
	currentPlayer->location.y = round(static_cast<float> ((map.GetSizeY() - 1) / 2));

	
	Player* tempPlayer = allPlayers.GetPlayer("Player2");
	tempPlayer->texture = allTextures.GetTexture("DirMarker2");
	tempPlayer->location.x = round(static_cast<float> (map.GetSizeX() - 50));
	tempPlayer->location.y = round(static_cast<float> (map.GetSizeY() - 50));
	

	for (auto& wep : allWeapons.weaponList)
		currentPlayer->AddWeapon(wep);

	if (HardwareCursor)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);

	for (int i = 0; i < map.GetSizeX(); i++)
		for (int n = 0; n < map.GetSizeY(); n++)
			if ((n == 0 || n == map.GetSizeY() - 1) || (i == 0 || i == map.GetSizeX() - 1))
				map.SetDataAt(i, n, MapDataType::Wall, baseWallHealth);

	map.SetDataAt(499, 500, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(499, 499, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(500, 500, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(500, 499, MapDataType::Wall, baseWallHealth);

	// Map test data.
	map.SetDataAt(50, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(51, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(52, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(53, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(54, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(55, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(56, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(57, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(58, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(59, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(60, 100, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(61, 100, MapDataType::Wall, baseWallHealth);

	map.SetDataAt(51, 99, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(51, 101, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(52, 98, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(52, 102, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(53, 97, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(53, 103, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(54, 96, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(54, 104, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(55, 95, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(55, 105, MapDataType::Wall, baseWallHealth);

	map.SetDataAt(100, 50, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 51, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 52, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 53, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 54, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 55, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 56, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 57, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 58, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 59, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 60, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(100, 61, MapDataType::Wall, baseWallHealth);

	map.SetDataAt(99, 51, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(101, 51, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(98, 52, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(102, 52, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(97, 53, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(103, 53, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(96, 54, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(104, 54, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(95, 55, MapDataType::Wall, baseWallHealth);
	map.SetDataAt(105, 55, MapDataType::Wall, baseWallHealth);

	for (int i = map.GetSizeX() - 200; i <= map.GetSizeX() - 100; i++)
		for (int n = 100; n <= map.GetSizeY() - 100; n++)
			map.SetDataAt(i, n, MapDataType::Wall, baseWallHealth);

	debug.Log("Setup+Shutdown", "SetupEngine", "Setup completed");

	return true;
}

// Shutdown the engine, cleaning up everything as required.
void ShutdownEngine()
{
	debug.Log("Setup+Shutdown", "ShutdownEngine", "Shutting down engine...");
	   
	// Destroy the main renderer before shutdown.
	if (mainRenderer != nullptr)
		SDL_DestroyRenderer(mainRenderer);

	// Destroy the surface used for drawing particles.
	if (mainSurface != nullptr)
		SDL_FreeSurface(mainSurface);

	// Destroy the main window before shutdown.
	if (mainWindow != nullptr)
		SDL_DestroyWindow(mainWindow);
	
	// Clear out all the arrays of data.
	allWeapons.RemoveAllWeapons();
	allPlayers.DeleteAllPlayers();
	allProjectiles.DestroyAllProjectiles();
	allTextures.Cleanup();
	allSounds.Cleanup();

	// Shutdown SDL.	
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	debug.Log("Setup+Shutdown", "ShutdownEngine", "Shutdown completed");
}