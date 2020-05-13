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
	return ((static_cast<float> (rand()) / static_cast<float> (RAND_MAX)) * (max - min)) + min;
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

// Gets every single point in the line between two x/y coords.
// https://stackoverflow.com/questions/10060046/drawing-lines-with-bresenhams-line-algorithm
std::vector<SDL_Point> GetAllMapDataBetweenPoints(int x1, int y1, int x2, int y2)
{
	std::vector<SDL_Point> points;

    {
        int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
        dx = x2 - x1;
        dy = y2 - y1;
        dx1 = fabs(dx);
        dy1 = fabs(dy);
        px = 2 * dy1 - dx1;
        py = 2 * dx1 - dy1;
        if (dy1 <= dx1)
        {
            if (dx >= 0)
            {
                x = x1;
                y = y1;
                xe = x2;
            }
            else
            {
                x = x2;
                y = y2;
                xe = x1;
            }
            points.push_back(SDL_Point{ x, y });
            for (i = 0; x < xe; i++)
            {
                x = x + 1;
                if (px < 0)
                {
                    px = px + 2 * dy1;
                }
                else
                {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    {
                        y = y + 1;
                    }
                    else
                    {
                        y = y - 1;
                    }
                    px = px + 2 * (dy1 - dx1);
                }
                points.push_back(SDL_Point{ x, y });
            }
        }
        else
        {
            if (dy >= 0)
            {
                x = x1;
                y = y1;
                ye = y2;
            }
            else
            {
                x = x2;
                y = y2;
                ye = y1;
            }
            points.push_back(SDL_Point{ x, y });
            for (i = 0; y < ye; i++)
            {
                y = y + 1;
                if (py <= 0)
                {
                    py = py + 2 * dx1;
                }
                else
                {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    {
                        x = x + 1;
                    }
                    else
                    {
                        x = x - 1;
                    }
                    py = py + 2 * (dx1 - dy1);
                }
                points.push_back(SDL_Point{ x, y });
            }
        }
    }

	return points;
}