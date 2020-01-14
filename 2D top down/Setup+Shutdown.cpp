#include "Setup+Shutdown.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Globals.h"
#include "Texture.h"

bool Setup()
{
	debug.showMessagesOnConsole = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		debug.LogError("Setup+Shutdown", "Setup", "SDL failed to initialize", SDL_GetError());
		return false;
	}

	if (TTF_Init() != 0)
	{
		debug.LogError("Setup+Shutdown", "Setup", "TTF failed to initialize", SDL_GetError());
		return false;
	}

	// Create main window.
	const int WINDOW_WIDTH = windowWidth;
	const int WINDOW_HEIGHT = windowHeight;

	Uint32 windowFlags = SDL_WINDOW_OPENGL;
	mainWindow = SDL_CreateWindow(programName.c_str(), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

	mainSurface = SDL_GetWindowSurface(mainWindow);

	Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, renderFlags);	

	Texture* tempTex = textures.CreateTexture("\\2D Top Down\\Resources\\Direction Marker.png", "DirMarker");

	if (tempTex == nullptr)
	{
		debug.LogError("Setup+Shutdown", "Setup", "failed to load Direction Marker.png", SDL_GetError());
		return false;
	}

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