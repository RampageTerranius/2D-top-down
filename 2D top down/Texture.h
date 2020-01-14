#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>

class Texture
{
public:
	Texture();
	~Texture();

	void Clear();
	bool Load(std::string fileLoc, std::string name);

	std::string Name() { return name; };
	SDL_Texture* Tex() { return tex; };
	SDL_Rect Rect() { return rect; };
	int W() { return w; };
	int H() { return h; };


private:
	std::string name;
	SDL_Texture* tex;
	SDL_Rect rect;
	int w, h;
};

class Textures
{
private:
	std::vector<Texture> textureList;

public:
	void Cleanup();
	Texture* GetTexture(std::string name);
	Texture* CreateTexture(std::string fileLoc, std::string name);
	void DeleteTexture(std::string name);
};