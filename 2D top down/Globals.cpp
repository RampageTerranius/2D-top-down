#include "Globals.h"

Debug debug = Debug();

std::string programName = "Test";

bool running = false;
bool HardwareCursor = false;

int windowWidth = 640;
int windowHeight = 480;

SDL_Window* mainWindow = nullptr;
SDL_Renderer* mainRenderer = nullptr;
SDL_Surface* mainSurface = nullptr;

Textures allTextures = Textures();
Projectiles allProjectiles = Projectiles();
Weapons allWeapons = Weapons();
Players allPlayers = Players();

Player* testPlayer;
SDL_Rect camera = {0, 0, windowWidth, windowHeight};


// Map data;
Map map = Map(1000, 1000);

int baseWallHealth = 20;

TTF ttfFPS = TTF();
TTF ttfWeapon = TTF();
TTF ttfAmmo = TTF();
TTF ttfDodges = TTF();