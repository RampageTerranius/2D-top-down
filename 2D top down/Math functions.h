#pragma once

#include <math.h>

// Get the distance between two different points.
float GetDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// Get the angle that the 2nd point is from the first.
float GetAngle(double x1, double y1, double x2, double y2)
{
	return atan2(y1 - y2, x1 - x2);
}

// Get the angle that the 2nd point is from the first.
float GetAngleAsDegrees(double x1, double y1, double x2, double y2)
{
	return (((float)GetAngle(x1, y1, x2, y2) * 180) / M_PI) - 90;// TODO: the math function is always 90 degrees ahead of what it should be and needs to be minus by 90, find out why.
}