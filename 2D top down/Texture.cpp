#include "Texture.h"

#include "Globals.h"

Texture::Texture()
{
	name = "";
	tex = nullptr;
	rect = SDL_Rect();
}

Texture::~Texture()
{
	Clear();
}

void Texture::Clear()
{
	if (tex != nullptr)
		SDL_DestroyTexture(tex);

	tex = nullptr;

	rect = SDL_Rect();
}

bool Texture::Load(std::string fileLoc, std::string name)
{
	SDL_Surface* surface;

	// Use base SDL_Image loadign function
	surface = IMG_Load(fileLoc.c_str());

	if (surface == nullptr)
		return false;

	// Setup the default source rect
	rect.x = 0;
	rect.y = 0;
	rect.w = surface->w;
	rect.h = surface->h;

	// Set the color key for transparency as RGB(255, 0 , 255)
	SDL_SetColorKey(surface, true, SDL_MapRGB(surface->format, 255, 255, 255));

	// Create the new texture
	tex = SDL_CreateTextureFromSurface(mainRenderer, surface);

	// Clear out the old surface
	SDL_FreeSurface(surface);

	if (tex == nullptr)
		return false;

	this->name = name;

	return true;
}

void Textures::Cleanup()
{
	for (auto& texture : textureList)
		texture.Clear();
}

Texture* Textures::GetTexture(std::string name)
{
	for (auto& tex : textureList)
		if (tex.Name() == name)
			return &tex;

	return nullptr;
}

Texture* Textures::CreateTexture(std::string fileLoc, std::string name)
{
	Texture tex;
	if (!tex.Load(fileLoc, name))
		return false;

	textureList.push_back(tex);

	return &textureList.back();
}

void Textures::DeleteTexture(std::string name)
{
	int i = 0;
	for (auto& tex : textureList)
	{
		if (tex.Name() == name)
		{
			textureList.erase(textureList.begin() + i);
			break;
		}
		i++;
	}
}