#pragma once

#include <SDL.h>
#include <string>
#include "Debug.h"
#include "Entity.h"
#include "Map.h"
#include "Texture.h"
#include "TTF.h"
#include "Character.h"
#include "Projectile.h"
#include "Weapon.h"

// Debugging stuff.
extern Debug debug;

// General application settings.
extern std::string programName;
extern int windowWidth;
extern int windowHeight;
extern bool HardwareCursor;

// SDL renderer/window.
extern SDL_Window* mainWindow;
extern SDL_Renderer* mainRenderer;
extern SDL_Surface* mainSurface;

// Other stuff.
extern bool running;

// Lists.
extern Textures allTextures;
extern Projectiles allProjectiles;
extern Weapons allWeapons;
extern Players allPlayers;

// Test Player.
extern Player* testPlayer;
extern SDL_Rect camera;

// Map data;
extern Map map;

extern int baseWallHealth;

// TTF Fonts.
extern TTF ttfFPS;
extern TTF ttfWeapon;
extern TTF ttfAmmo;
extern TTF ttfDodges;