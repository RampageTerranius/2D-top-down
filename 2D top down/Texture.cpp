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
	debug.Log("Texture", "Texture::Load", "Attempting to load texture at location : " + fileLoc);

	if (tex != nullptr)
	{
		debug.Log("Texture", "Texture::Load", "A texture is already loaded in this object");
		return false;
	}

	SDL_Surface* surface;

	// Use base SDL_Image loadign function
	surface = IMG_Load(fileLoc.c_str());

	if (surface == nullptr)
	{
		std::string str = SDL_GetError();
		debug.Log("Texture", "Texture::Load", "Failed to load image " + str);
		return false;
	}

	// Setup the default source rect
	rect.x = 0;
	rect.y = 0;
	rect.w = surface->w;
	rect.h = surface->h;

	// Set the color key for transparency as RGB(255, 0 , 255)
	SDL_SetColorKey(surface, true, SDL_MapRGB(surface->format, 255, 0, 255));

	// Create the new texture
	tex = SDL_CreateTextureFromSurface(mainRenderer, surface);

	// Clear out the old surface
	SDL_FreeSurface(surface);

	if (tex == nullptr)
	{
		std::string str = SDL_GetError();
		debug.Log("Texture", "Texture::Load", "Failed to create texture from image " + str);
		return false;
	}

	this->name = name;

	return true;
}

void Textures::Cleanup()
{
	for (auto& texture : textureList)
		texture->Clear();
}

Texture* Textures::GetTexture(std::string name)
{
	for (auto& tex : textureList)
		if (tex->Name() == name)
			return tex;

	return nullptr;
}

Texture* Textures::CreateTexture(std::string fileLoc, std::string name)
{
	Texture* tex = new Texture();
	if (!tex->Load(fileLoc, name))
	{
		delete tex;
		return false;
	}

	textureList.push_back(tex);

	return textureList.back();
}

void Textures::DeleteTexture(std::string name)
{
	int i = 0;
	for (auto& tex : textureList)
	{
		if (tex->Name() == name)
		{
			textureList.erase(textureList.begin() + i);
			break;
		}
		i++;
	}
}