#include "Math functions.h"
#include "Globals.h"
#include "EventHandler.h"

#include <SDL.h>

#include <math.h>
#include <cstdlib>


// Get the distance between two different points.
double GetDistance(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;

	return sqrt((x * x) + (y * y));
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
	return ((static_cast<float> (rand()) / static_cast<float> (RAND_MAX)) * (max - min)) + min;
}

// Gets the X/Y coordinate on the map of where the cursor is pointing.
SDL_Point GetMapCoordFromCursor()
{
	SDL_Point mapCoord = { 0, 0 };

	// Convert mouse and camera into the location on the map we are pointing at.
	SDL_Point mouse = iManager->GetMouseLocation();

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

// Gets every single point in the line between two x/y coords.
// https://gist.github.com/bert/1085538#file-plot_line-c
std::vector<SDL_Point> GetAllMapDataBetweenPoints(int x0, int y0, int x1, int y1)
{
	std::vector<SDL_Point> points;

	{
		int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		int err = dx + dy, e2; /* error value e_xy */

		for (;;) {  /* loop */
			points.push_back({ x0, y0 });
			if (x0 == x1 && y0 == y1) break;
			e2 = 2 * err;
			if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
			if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
		}
	}

	return points;
}