#include "Character.h"
#include "UI.h"
#include "Mouse.h"
#include "globals.h"
#include "Math functions.h"

bool Character::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.x = (int)round(xLoc);
		rect.y = (int)round( yLoc);
		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		rect.x -= (int)round((float)rect.w / 2);
		rect.y -= (int)round((float)rect.h / 2);

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, ((double)directionFacing + 90), NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Entity", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

// Logic for determining how the player is moving, refer to EventHandle for how xVel and yVel is determined.
void Player::MovePlayerAccordingToInput()
{
	switch (xVel)
	{
	case -1:
		if (sprinting)
			MoveObjectBy(-(float)sprintVel, 0);
		else
			MoveObjectBy(-(float)walkVel, 0);
		break;
	case 1:
		if (sprinting)
			MoveObjectBy((float)sprintVel, 0);
		else
			MoveObjectBy((float)walkVel, 0);
		break;
	}

	switch (yVel)
	{
	case -1:
		if (sprinting)
			MoveObjectBy(0, -(float)sprintVel);
		else
			MoveObjectBy(0, -(float)walkVel);
		break;
	case 1:
		if (sprinting)
			MoveObjectBy(0, (float)sprintVel);
		else
			MoveObjectBy(0, (float)walkVel);
		break;
	}
}

// Logic for the player firign their weapon.
void Player::FireWeapon(SDL_Point aimLoc)
{
	if (weapon != nullptr)
		if (ammoLeft > 0)
		{
			if (reloadTimer == 0 && fireTimer == 0)
			{
				// Get the point of the player.
				SDL_Point plPoint;
				plPoint.x = (int)round(testPlayer->xLoc);
				plPoint.y = (int)round(testPlayer->yLoc);

				// Calculate deviation/recoil etc.
				float calcDeviation = weapon->deviation + currentRecoil;

				float randomDeviationX = RandomFloat(-(calcDeviation / 2), calcDeviation / 2);
				float randomDeviationY = RandomFloat(-(calcDeviation / 2), calcDeviation / 2);

				aimLoc.x += (int)round(randomDeviationX);
				aimLoc.y += (int)round(randomDeviationY);

				// Create the projectile.
				allProjectiles.CreateProjectile(plPoint, aimLoc, weapon);

				debug.Log("Character", "FireWeapon", "fired round. deviation of :" + std::to_string(calcDeviation));

				currentRecoil += weapon->recoil;
				if (currentRecoil > weapon->maxDeviation)
					currentRecoil = weapon->maxDeviation;

				fireTimer = weapon->fireRate;

				ammoLeft--;

				return;
			}
			// TODO: player tryed to fire while gun was reloading/between shots. make a sound or something to let the player know.
		}
		else
			ReloadWeapon();// Player had no ammo, goto reload logic.		
}

void Player::RenderAimer()
{
	// Render the test players aimer.
	UI aimer = UI();

	// TODO: bottom and right aimer are 1 pixel off and need to be minused by 1, fix this.

	aimer.texture = allTextures.GetTexture("AimMarkerTop");
	aimer.xLoc = (float)mouse.x;
	aimer.yLoc = ((float)mouse.y - ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) - (aimer.texture->Rect().h);
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("AimMarkerBottom");
	aimer.xLoc = (float)mouse.x;
	aimer.yLoc = ((float)mouse.y + ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) + (aimer.texture->Rect().h) - 1;
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("AimMarkerLeft");
	aimer.xLoc = ((float)mouse.x - ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) - (aimer.texture->Rect().w);
	aimer.yLoc = (float)mouse.y;
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("AimMarkerRight");
	aimer.xLoc = ((float)mouse.x + ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) + (aimer.texture->Rect().w) - 1;
	aimer.yLoc = (float)mouse.y;
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("RedDot");
	aimer.xLoc = (float)mouse.x;
	aimer.yLoc = (float)mouse.y;
	aimer.Render(0);
}

// Start maknig the player reload their weapon.
void Player::ReloadWeapon()
{
	if (reloadTimer == 0)
		reloadTimer = weapon->reloadTime;
}

Player* Players::CreatePlayer(std::string playerName)
{
	Player* pl = new Player();

	pl->texture = allTextures.GetTexture("DirMarker");

	playerList.push_back(pl);

	debug.Log("Character", "Players::CreatePlayer", "Created a player of name: " + playerName);

	return playerList.back();
}

void Players::DeletePlayer(std::string playerName)
{
	int i = 0;

	for (Player* pl : playerList)
	{
		if (pl->name == playerName)
		{
			playerList.erase(playerList.begin() + i);
			debug.Log("Character", "Players::DeletePlayer", "Deleted a player of name: " +playerName);
			return;
		}

		i++;
	}

	debug.Log("Projectile", "DestroyProjectile", "Call to destroy a player of name: " + playerName + " has failed!");
}

Player* Players::GetPlayer(std::string playerName)
{
	for (Player* pl : playerList)
		if (pl->name == playerName)
			return pl;

	return nullptr;
}

void Players::RenderAllPlayers()
{
	for (auto& player : playerList)
		player->Render();
}

void Players::HandlePlayerEvents()
{
	for (Player* pl : playerList)
	{
		if (pl->reloadTimer > 0)
		{
			pl->reloadTimer--;
			if (pl->reloadTimer == 0)
				pl->ammoLeft = pl->weapon->totalAmmo;
		}

		if (pl->fireTimer > 0)
			pl->fireTimer--;

		if ((pl->currentRecoil > 0 && !pl->isFiring && pl->fireTimer == 0) || pl->reloadTimer != 0)
		{
			pl->currentRecoil-= pl->weapon->recoilControlRate;

			if (pl->currentRecoil < 0)
				pl->currentRecoil = 0;

			if (pl->isFiring)
				pl->currentRecoil = pl->currentRecoil;
		}
	}
}