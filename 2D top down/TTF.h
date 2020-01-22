#pragma once

#include "Globals.h"
#include "Entity.h"

#include <SDL.h>
#include <SDL_ttf.h>

class TTF : public Entity
{
public:
	bool Create(std::string ttfFile, int size, std::string text, int R, int G, int B, int A);
	bool ChangeText(int size, std::string text);
	bool IsActiveTTF();

private:
	std::string message;
	TTF_Font* font;
	int fontSize;
};

bool TTF::IsActiveTTF()
{
	if (message.empty() && font != nullptr)
		return true;

	return false;
}

bool TTF::Create(std::string ttfFile, int size, std::string text, int R, int G, int B, int A)
{
	// Make sure we dont already have data.
	if (IsActiveTTF())
	{
		debug.Log("TTF", "Create", "TTF object already has data, please use ChangeText to edit");
		return false;
	}

	// Open the font.
	font = TTF_OpenFont(ttfFile.c_str(), size);

	if (font == nullptr)
	{
		debug.Log("TTF", "Create", "Failed to load font at location " + ttfFile);
		return false;
	}

	SDL_Color col{ R, G, B, A };

	SDL_Surface* ttfSurface = NULL;
	ttfSurface = TTF_RenderText_Solid(font, message.c_str(), col);

	// If failed to crete the surface clean up and return the result.
	if (ttfSurface == nullptr)
	{
		TTF_CloseFont(font);
		return false;
	}

	SDL_Texture* tex;
	tex = SDL_CreateTextureFromSurface(mainRenderer, ttfSurface);

	textures.AddTexture(tex, text);

	fontSize = size;
	message = text;
}