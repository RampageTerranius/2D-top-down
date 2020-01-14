#include "Globals.h"

Debug debug = Debug();

std::string programName = "Test";

bool running = false;

int windowWidth = 800;
int windowHeight = 600;

SDL_Window* mainWindow = nullptr;
SDL_Renderer* mainRenderer = nullptr;
SDL_Surface* mainSurface = nullptr;

Textures textures = Textures();
Player pl = Player();