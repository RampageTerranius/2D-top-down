#include "Math functions.h"
#include "Globals.h"
#include "Mouse.h"

#include <SDL.h>

#include <math.h>
#include <cstdlib>


// Get the distance between two different points.
double GetDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// Get the angle that the 2nd point is from the first.
double GetAngle(double x1, double y1, double x2, double y2)
{
	return atan2(y2 - y1, x2 - x1);
}

// Get the angle that the 2nd point is from the first.
double GetAngleAsDegrees(double x1, double y1, double x2, double y2)
{
	return atan2(y2 - y1, x2 - x1) * 180 / M_PI;
}

float RandomFloat(float min, float max)
{
	return (((float)rand() / (float)RAND_MAX) * (max - min)) + min;
}

// Gets the X/Y coordinate on the map of where the cursor is pointing.
SDL_Point GetMapCoordFromCursor()
{
	SDL_Point mapCoord = { 0, 0 };

	// Convert mouse and camera into the location on the map we are pointing at.
	mapCoord.x = mouse.x - camera.x;
	mapCoord.y = mouse.y - camera.y;

	return mapCoord;
}

// Gets the X/Y coordinate on the screen where the given point would be.
// This does not factor for the coord potentially being off the screen, it is up to the user to determine this.
SDL_Point GetScreenCoordFromMapPoint(SDL_Point point)
{
	SDL_Point mapCoord = { 0, 0 };

	// Convert mouse and camera into the location on the map we are pointing at.
	mapCoord.x = camera.x + point.x;
	mapCoord.y = camera.y + point.y;

	return mapCoord;
}