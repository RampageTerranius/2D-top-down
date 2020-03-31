#include "Math functions.h"

#include <SDL.h>

#include <math.h>

// Get the distance between two different points.
double GetDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// Get the angle that the 2nd point is from the first.
double GetAngle(double x1, double y1, double x2, double y2)
{
	return atan2(y1 - y2, x1 - x2);
}

// Get the angle that the 2nd point is from the first.
double GetAngleAsDegrees(double x1, double y1, double x2, double y2)
{
	return atan2(y2 - y1, x2 - x1) * 180 / M_PI;// TODO: the math function is always 90 degrees ahead of what it should be and needs to be minus by 90, find out why.
}