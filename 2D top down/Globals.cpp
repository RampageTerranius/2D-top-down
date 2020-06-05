#include "Globals.h"

std::string programName = "Test";

bool HardwareCursor = false;

InputManager* iManager = new InputManager();

int windowWidth = 640;
int windowHeight = 480;
int windowWidthDiv2 = windowWidth / 2;
int windowHeightDiv2 = windowHeight / 2;

int renderColorR = 20;
int renderColorG = 20;
int renderColorB = 20;
int renderColorA = 255;

SDL_Window* mainWindow = nullptr;
SDL_Renderer* mainRenderer = nullptr;
SDL_Surface* mainSurface = nullptr;

Textures allTextures = Textures();
Projectiles allProjectiles = Projectiles();
Weapons allWeapons = Weapons();
Players allPlayers = Players();
Sounds allSounds = Sounds();

Player* currentPlayer;
SDL_Rect camera = {0, 0,};

// Frame rate.
int frameRate = 60;
int ticksPerFrame = 1000 / frameRate;
bool capFrameRate = true;

TTF ttfFPS = TTF();
TTF ttfWeapon = TTF();
TTF ttfAmmo = TTF();
TTF ttfDodges = TTF();

// Timers.
Timer fpsTimer = Timer();
Timer capTimer = Timer();
float avgFPS = 0;

Uint32 frametimes[FRAME_TIMERS];
Uint32 frametimelast = SDL_GetTicks();
Uint32 totalFramesCounted = 0;