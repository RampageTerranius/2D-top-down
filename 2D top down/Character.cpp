#include "Character.h"
#include "globals.h"

void Player::MovePlayerAccordingToInput()
{
	switch (xVel)
	{
	case -1:
		if (sprinting)
			MoveObjectBy(-sprintVel, 0);
		else
			MoveObjectBy(-walkVel, 0);
		break;
	case 1:
		if (sprinting)
			MoveObjectBy(sprintVel, 0);
		else
			MoveObjectBy(walkVel, 0);
		break;
	}

	switch (yVel)
	{
	case -1:
		if (sprinting)
			MoveObjectBy(0, -sprintVel);
		else
			MoveObjectBy(0, -walkVel);
		break;
	case 1:
		if (sprinting)
			MoveObjectBy(0, sprintVel);
		else
			MoveObjectBy(0, walkVel);
		break;
	}
}

bool Character::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.x = xLoc;
		rect.y = yLoc;
		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		rect.x -= (rect.w / 2);
		rect.y -= (rect.h / 2);

		if (SDL_RenderCopyEx(mainRenderer, pl.texture->Tex(), NULL, &rect, directionFacing + 90, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}
