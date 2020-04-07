#include "Globals.h"

Debug debug = Debug();

std::string programName = "Test";

bool running = false;
bool HardwareCursor = false;

int windowWidth = 800;
int windowHeight = 600;

SDL_Window* mainWindow = nullptr;
SDL_Renderer* mainRenderer = nullptr;
SDL_Surface* mainSurface = nullptr;

Textures allTextures = Textures();
Projectiles allProjectiles = Projectiles();
Weapons allWeapons = Weapons();
Players allPlayers = Players();
Player* testPlayer;

extern TTF ttfFPS = TTF();
extern TTF ttfWeapon = TTF();
extern TTF ttfAmmo = TTF();
extern TTF ttfDodges = TTF();