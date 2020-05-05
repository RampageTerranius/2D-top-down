#pragma once

#include "Map Data Type.h"

#include <vector>

// This class is used for storing the data for the map (handled in what is effectivly a pixel format).
// Please keep in mind that SDL treats the top left corner as coordinate 0/0 so we will treat it the same.
class Map
{
public:
	Map(int x, int y);

	int GetSizeX() { return sizeX; }
	int GetSizeY() { return sizeY; }
	MapDataType GetDataAt(int x, int y);
	bool SetDataAt(int x, int y, MapDataType newType);
	void Render();

private:
	int sizeX;
	int sizeY;

	MapDataType** mapData;
};