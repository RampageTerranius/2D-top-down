#include "Map.h"
#include "Globals.h"
#include <SDL.h>

// Map data;
Map map = Map(1000, 1000);

int baseWallHealth = 1;

// Basic constructor for automatically creating the map at the given size.
Map::Map(int newSizeX, int newSizeY)
{
	Create(newSizeX, newSizeY);
}

Map::~Map()
{	
	Delete();
}

void Map::Create(int newSizeX, int newSizeY)
{
	// We need to know the total size of the map
	sizeX = newSizeX;
	sizeY = newSizeY;

	mapData = new MapData * [sizeY];
	for (int i = 0; i < sizeY; ++i)
		mapData[i] = new MapData[sizeX];

	for (int i = 0; i < sizeY; i++)
		for (int n = 0; n < sizeX; n++)
		{
			mapData[i][n].type = MapDataType::Empty;
			mapData[i][n].health = 0;
		}
}

void Map::Delete()
{
	for (int i = 0; i < sizeY; ++i)
	{
		delete mapData[i];
		mapData[i] = nullptr;
	}

	delete mapData;
	mapData = nullptr;
}

MapDataType Map::GetTypeAt(int x, int y)
{
	// Attempt to get the data at the given location.
	if (x >= 0 && x < sizeX)
		if (y >= 0 && y < sizeY)
			return mapData[x][y].type;

	// If there is any issues return an unknown data type.		
	return MapDataType::Unknown;
}

int Map::GetHealthAt(int x, int y)
{
	// Attempt to get the data at the given location.
	if (x >= 0 && x < sizeX)
		if (y >= 0 && y < sizeY)
			return mapData[x][y].health;

	// If there is any issues return an unknown data type.		
	return -1;
}

bool Map::SetDataAt(int x, int y, MapDataType newType, int newHealth)
{
	// Attempt to set the data at the given location.
	if (x >= 0 && x < sizeX)
		if (y >= 0 && y < sizeY)
		{
			mapData[x][y].type = newType;
			mapData[x][y].health = newHealth;
			return true;
		}

	// If there is any issues return false.		
	return false;
}

// http://sdl.beuc.net/sdl.wiki/Pixel_Access
void EditPixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16*)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32*)p = pixel;
		break;
	}
}

// Renders the map onto the screen.
// This is done BEFORE anything else so as such it will always be the back layer.
void Map::Render()
{
	SDL_Surface* tempSurf = nullptr;

	tempSurf = SDL_CreateRGBSurface(0, sizeX, sizeY, 32, 0, 0, 0, 0);

	SDL_FillRect(tempSurf, nullptr, 0x000000);

	for (int i = 0; i < sizeY; i++)
		for (int n = 0; n < sizeX; n++)
			switch (mapData[n][i].type)
			{
			case MapDataType::Wall:
				SDL_LockSurface(tempSurf);
				EditPixel(tempSurf, n, i, SDL_MapRGB(tempSurf->format, 80, 40, 0));
				SDL_UnlockSurface(tempSurf);
				break;
			}

	SDL_Texture* tempTex = SDL_CreateTextureFromSurface(mainRenderer, tempSurf);
	SDL_FreeSurface(tempSurf);	

	SDL_Rect src = { 0, 0, 0, 0 };
	SDL_QueryTexture(tempTex, NULL, NULL, &src.w, &src.h);

	SDL_RenderCopy(mainRenderer, tempTex, &src, &camera);

	SDL_DestroyTexture(tempTex);
	tempTex = nullptr;
}