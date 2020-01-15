#include "Setup+Shutdown.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <PathCch.h>

#include "Globals.h"
#include "Texture.h"

std::string GetEXEPath()
{
	char exePath[MAX_PATH];

	GetModuleFileName(NULL, exePath, sizeof(exePath));

	std::string tempStr = exePath;

	size_t pos = tempStr.find_last_of("\\");

	if (pos != std::string::npos)
		return tempStr.substr(0, pos + 1);

	return "";
}

bool Setup()
{
	debug.showMessagesOnConsole = true;

	debug.Log("Setup+Shutdown", "Setup", "Starting setup...");

	debug.Log("Setup+Shutdown", "Setup", "Initializing SDL sub-routines...");

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

	pl.texture = textures.CreateTexture(GetEXEPath() + "\\Direction Marker.png", "DirMarker");

	if (pl.texture == nullptr)
	{
		debug.Log("Setup+Shutdown", "Setup", "failed to load Direction Marker.png");
		return false;
	}

	pl.point.x = (windowWidth / 2) - (pl.texture->Rect().w / 2);
	pl.point.y = (windowHeight / 2) - (pl.texture->Rect().h / 2);

	debug.Log("Setup+Shutdown", "Setup", "Setup completed");



	return true;
}

void Shutdown()
{
	// Destroy the main window before shutdown.
	if (mainWindow != nullptr)
	{
		SDL_DestroyWindow(mainWindow);
		mainWindow = nullptr;
	}

	// Destroy the surface used for drawing particles.
	if (mainSurface != nullptr)
	{
		SDL_FreeSurface(mainSurface);
		mainSurface = nullptr;
	}

	// Destroy the main renderer before shutdown.
	if (mainRenderer != nullptr)
	{
		SDL_DestroyRenderer(mainRenderer);
		mainRenderer = nullptr;
	}
	   
	SDL_Quit();
}