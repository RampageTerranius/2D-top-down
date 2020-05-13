#pragma once

#include <SDL.h>
#include <vector>

// Get the distance between two different points.
double GetDistance(double x1, double y1, double x2, double y2);

// Get the angle that the 2nd point is from the first.
double GetAngle(double x1, double y1, double x2, double y2);

// Get the angle that the 2nd point is from the first.
double GetAngleAsDegrees(double x1, double y1, double x2, double y2);

float RandomFloat(float min, float max);

// Gets the X/Y coordinate on the map of where the cursor is pointing.
SDL_Point GetMapCoordFromCursor();

// Gets the X/Y coordinate on the screen where the given point would be.
// This does not factor for the coord potentially being off the screen, it is up to the user to determine this.
SDL_Point GetScreenCoordFromMapPoint(SDL_Point point);

// Gets every single point in the line between two x/y coords.
std::vector<SDL_Point> GetAllMapDataBetweenPoints(int x0, int y0, int x1, int y1);