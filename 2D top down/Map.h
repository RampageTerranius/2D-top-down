#pragma once

#include "Map Data Type.h"

#include <vector>

class MapData
{
public:
	int health;
	MapDataType type;
};

// This class is used for storing the data for the map (handled in what is effectivly a pixel format).
// Please keep in mind that SDL treats the top left corner as coordinate 0/0 so we will treat it the same.
class Map
{
public:
	Map(int x, int y);
	~Map();
	
	void Create(int newSizeX, int newSizeY);
	void Delete();
	int GetSizeX() { return sizeX; }
	int GetSizeY() { return sizeY; }
	MapDataType GetTypeAt(int x, int y);
	int GetHealthAt(int x, int y);
	bool SetDataAt(int x, int y, MapDataType newType, int newHealth);
	void Render();

private:
	int sizeX;
	int sizeY;

	MapData** mapData;
};