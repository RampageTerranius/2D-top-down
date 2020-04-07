#pragma once

#include <SDL.h>
#include <string>
#include "Debug.h"
#include "Entity.h"
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

// SDL renderer/window.
extern SDL_Window* mainWindow;
extern SDL_Renderer* mainRenderer;
extern SDL_Surface* mainSurface;

extern bool running;
extern bool HardwareCursor;

extern Textures allTextures;
extern Projectiles allProjectiles;
extern Weapons allWeapons;
extern Players allPlayers;

extern Player* testPlayer;

extern TTF ttfFPS;
extern TTF ttfWeapon;
extern TTF ttfAmmo;
extern TTF ttfDodges;