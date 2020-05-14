#include "Character.h"
#include "UI.h"
#include "Mouse.h"
#include "globals.h"
#include "Math functions.h"

Character::Character()
{
	this->ammoLeft = 0;
	this->directionFacing = 0;
	this->fireTimer = 0;
	this->ID = 0;
	this->reloadTimer = 0;
	this->texture = nullptr;
	this->weapon = nullptr;
	this->xLoc = 0;
	this->yLoc = 0;
}

bool Character::Render()
{
	if (texture != nullptr)
	{
		SDL_Rect rect;

		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;
		rect.x = static_cast<int> (round((windowWidth / 2) - (rect.w / 2)));
		rect.y = static_cast<int> (round((windowHeight / 2) - (rect.h / 2)));

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, directionFacing + 90.0, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Character", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

Player::Player()
{
	Character();

	this->name = "";

	this->health = 0;

	this->currentRecoil = 0;
	this->isFiring = 0;

	this->xVel = 0;// -1 = left 0 = none 1 = right
	this->yVel = 0;// -1 = up 0 = none 1 = down

	this->baseMovementVel = 4;
	this->dodgeVel = 24;
	this->dodgeVelDrop = 2;

	this->currentMovementVel = baseMovementVel;

	this->dodgesLeft = 3;
	this->totalDodges = 3;
	this->dodgeBaseRechargeTime = 120;
	this->dodgeChargeTimer = 0;
}

// Logic for determining how the player is moving, refer to EventHandle for how xVel and yVel is determined.
void Player::MovePlayerAccordingToInput()
{	
	switch (xVel)
	{
	case -1:
		MoveBy(-currentMovementVel, 0);
		break;
	case 1:
		MoveBy(currentMovementVel, 0);
		break;
	}

	switch (yVel)
	{
	case -1:
		MoveBy(0, -currentMovementVel);
		break;
	case 1:
		MoveBy(0, currentMovementVel);
		break;
	}

	// TODO: camera is currently calculating ALL players, this will need to be updated in the future.
	camera.x = static_cast<int> ((windowWidth/2) - testPlayer->xLoc);
	camera.w = map.GetSizeX();
	camera.y = static_cast<int> ((windowHeight/2) - testPlayer->yLoc);
	camera.h = map.GetSizeY();
}

// Logic for the player firing their weapon.
void Player::FireWeapon()
{
	if (this->weapon != nullptr)
		if (this->ammoLeft > 0)
		{
			if ((this->reloadTimer == 0 && this->fireTimer == 0) || (this->weapon->fireType == RELOADTYPE_SINGLE && this->fireTimer == 0))
			{
				this->reloadTimer = 0;
				
				// Get the point of the player.
				SDL_Point plPoint;
				plPoint.x = static_cast<int> (round(testPlayer->xLoc));
				plPoint.y = static_cast<int> (round(testPlayer->yLoc));

				int tempProjectilesToLaunch = this->weapon->bulletsPerShot;

				float calcDeviation = 0.0;

				while (tempProjectilesToLaunch > 0)
				{
					SDL_Point aimLoc = GetMapCoordFromCursor();

					// Calculate deviation/recoil etc.
					calcDeviation = weapon->deviation + currentRecoil;

					float randomDeviationX = RandomFloat(-(calcDeviation / 2), calcDeviation / 2);
					float randomDeviationY = RandomFloat(-(calcDeviation / 2), calcDeviation / 2);

					aimLoc.x += static_cast<int> (round(randomDeviationX));
					aimLoc.y += static_cast<int> (round(randomDeviationY));

					// Create the projectile.
					allProjectiles.CreateProjectile(plPoint, aimLoc, this->weapon, this);

					tempProjectilesToLaunch--;
				}

				debug.Log("Character", "FireWeapon", "fired round. deviation of :" + std::to_string(calcDeviation));

				this->currentRecoil += this->weapon->recoil;
				if (currentRecoil > this->weapon->maxDeviation)
					currentRecoil = this->weapon->maxDeviation;

				this->fireTimer = this->weapon->fireRate;

				this->ammoLeft--;

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
	aimer.xLoc = static_cast<float> (mouse.x);
	aimer.yLoc = (static_cast<float> (mouse.y) - ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) - static_cast<float> (aimer.texture->Rect().h);
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("AimMarkerBottom");
	aimer.xLoc = static_cast<float> (mouse.x);
	aimer.yLoc = (static_cast<float> (mouse.y) + ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) + static_cast<float> (aimer.texture->Rect().h) - 1;
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("AimMarkerLeft");
	aimer.xLoc = (static_cast<float> (mouse.x) - ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) - static_cast<float> (aimer.texture->Rect().w);
	aimer.yLoc = static_cast<float> (mouse.y);
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("AimMarkerRight");
	aimer.xLoc = (static_cast<float> (mouse.x) + ((testPlayer->currentRecoil + testPlayer->weapon->deviation) / 2)) + static_cast<float> (aimer.texture->Rect().w) - 1;
	aimer.yLoc = static_cast<float> (mouse.y);
	aimer.Render(0);

	aimer.texture = allTextures.GetTexture("RedDot");
	aimer.xLoc = static_cast<float> (mouse.x);
	aimer.yLoc = static_cast<float> (mouse.y);
	aimer.Render(0);
}

// Start making the player reload their weapon.
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
				switch (pl->weapon->reloadType)
				{
				case RELOADTYPE_CLIP:
					pl->ammoLeft = pl->weapon->totalAmmo;
					break;

				case RELOADTYPE_SINGLE:
					if (pl->ammoLeft < pl->weapon->totalAmmo)
					{
						pl->ammoLeft++;
						pl->reloadTimer = pl->weapon->reloadTime;
					}
					break;
				}
		}

		if (pl->fireTimer > 0)
			pl->fireTimer--;

		if (pl->currentRecoil > 0/* && !pl->isFiring && pl->fireTimer == 0*/)
		{
			pl->currentRecoil-= pl->weapon->recoilControlRate;

			if (pl->currentRecoil < 0)
				pl->currentRecoil = 0;

			if (pl->isFiring)
				pl->currentRecoil = pl->currentRecoil;
		}

		if (pl->currentMovementVel > pl->baseMovementVel)
		{
			pl->currentMovementVel -= pl->dodgeVelDrop;
			if (pl->currentMovementVel < pl->baseMovementVel)
				pl->currentMovementVel = pl->baseMovementVel;
		}

		if (pl->dodgesLeft < pl->totalDodges)
		{
			pl->dodgeChargeTimer++;

			if (pl->dodgeChargeTimer >= pl->dodgeBaseRechargeTime)
			{
				pl->dodgesLeft++;
				pl->dodgeChargeTimer = 0;
			}
		}
	}
}