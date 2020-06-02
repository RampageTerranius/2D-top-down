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
#include "EventHandler.h"

// Debugging stuff.
extern Debug debug;

extern InputManager* iManager;

// General application settings.
extern std::string programName;
extern int windowWidth;
extern int windowHeight;
extern bool HardwareCursor;

extern int renderColorR;
extern int renderColorG;
extern int renderColorB;
extern int renderColorA;

// SDL renderer/window.
extern SDL_Window* mainWindow;
extern SDL_Renderer* mainRenderer;
extern SDL_Surface* mainSurface;

// Other stuff.

// Lists.
extern Textures allTextures;
extern Projectiles allProjectiles;
extern Weapons allWeapons;
extern Players allPlayers;

// Test Player.
extern Player* currentPlayer;
extern SDL_Rect camera;

// Map data;
extern Map map;

extern int baseWallHealth;
extern int projectileCalcsPerTick;

// TTF Fonts.
extern TTF ttfFPS;
extern TTF ttfWeapon;
extern TTF ttfAmmo;
extern TTF ttfDodges;