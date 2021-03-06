#include "Entity.h"

#include "Globals.h"
#include "Math functions.h"
#include "Vector2D.h"
#include "Debug.h"
#include "UI.h"

Entity::Entity()
{
	this->ID = 0;
	this->texture = nullptr;
	this->location = Vector2D(0, 0);
	this->target = Vector2D(0, 0);
	this->directionFacing = 0;
}

bool Entity::Render()
{
	if (this->texture != nullptr)
	{
		SDL_Rect rect;

		rect.w = texture->Rect().w;
		rect.h = texture->Rect().h;

		SDL_Point charPoint{ static_cast <int> (round(this->location.x)), static_cast <int> (round(this->location.y)) };

		SDL_Point mapPoint = GetScreenCoordFromMapPoint(charPoint);

		rect.x = static_cast<int> (mapPoint.x - (rect.w / 2));
		rect.y = static_cast<int> (mapPoint.y - (rect.h / 2));

		// TODO: modify this code to help keep rendering quick and fast
		// Probably best to make this check if its in range of the camera currenty
		/*if (!(rect.x >= (0 - rect.w) && rect.x < windowWidth))
			if (!(rect.y >= (0 - rect.h) && rect.y < windowHeight))
				return false;*/

		if (SDL_RenderCopyEx(mainRenderer, texture->Tex(), NULL, &rect, directionFacing, NULL, SDL_FLIP_NONE) >= 0)
			return true;
	}

	debug.Log("Character", "Render", "failed to render entity (" + std::to_string(ID) + ") : " + SDL_GetError());

	return false;
}

void Entity::CalculateDirectionFacing()
{
	this->directionFacing = static_cast <float> (GetAngleAsDegrees(this->location.x, this->location.y, this->target.x, this->target.y));
}

// Move the entity from its point of origin by the given X/Y.
void Entity::MoveBy(float x, float y)
{
	this->location.x += x;
	this->location.y += y;

	if (this->location.x <= 0)
		this->location.x = 0;
	else if (this->location.x >= static_cast<float> (map.GetSizeX()))
		this->location.x = static_cast<float> (map.GetSizeX() - 1);

	if (this->location.y <= 0)
		this->location.y = 0;
	if (this->location.y >= static_cast<float> (map.GetSizeY()))
		this->location.y = static_cast<float> (map.GetSizeY() - 1);
}

// Move the entity DIRECTLY to the given X/Y coords
void Entity::MoveTo(int x, int y)
{
	this->location.x = static_cast<float> (x);
	this->location.y = static_cast<float> (y);

	if (this->location.x <= 0)
		this->location.x = 0;
	else if (this->location.x >= static_cast<float> (map.GetSizeX()))
		this->location.x = static_cast<float> (map.GetSizeX() - 1);

	if (this->location.y <= 0)
		this->location.y = 0;
	if (this->location.y >= static_cast<float> (map.GetSizeY()))
		this->location.y = static_cast<float> (map.GetSizeY() - 1);
}

void Entity::MoveCameraToHere()
{
	camera.x = static_cast<int> (windowWidthDiv2 - round(this->location.x));
	camera.w = map.GetSizeX();
	camera.y = static_cast<int> (windowHeightDiv2 - round(this->location.y));
	camera.h = map.GetSizeY();
}

// Move the character from its point of origin by the given X/Y while also checking for collision with walls etc.
void Player::MoveBy(float x, float y)
{
	float tempX = this->location.x + x;
	float tempY = this->location.y + y;

	int pointsToMove = 0;

	std::vector<SDL_Point> points = GetAllMapDataBetweenPoints(static_cast<int> (round(this->location.x)), static_cast<int> (round(this->location.y)), static_cast<int> (round(tempX)), static_cast<int> (round(tempY)));

	// We need to NOT check the first point as the first point is the player.
	bool firstPoint = true;

	// Check how many points we will be moving.
	if (points.size() > 0)
		for (auto& point : points)
		{
			if (firstPoint)
			{
				firstPoint = false;
				continue;
			}

			if (map.GetTypeAt(point.x, point.y) == MapDataType::Empty)
				pointsToMove++;
			else
				break;
		}

	// Move the user and
	if (pointsToMove > 0)
	{
		this->location.x = (location.x + ((x / points.size()) * pointsToMove));
		this->location.y = (this->location.y + ((y / points.size()) * pointsToMove));

		if (this->location.x <= 0)
			this->location.x = 0;
		else if (this->location.x >= static_cast<float> (map.GetSizeX()))
			this->location.x = static_cast<float> (map.GetSizeX() - 1);

		if (this->location.y <= 0)
			this->location.y = 0;
		else if (this->location.y >= static_cast<float> (map.GetSizeY()))
			this->location.y = static_cast<float> (map.GetSizeY() - 1);
	}
}

Player::Player()
{
	Entity();

	this->name = "";

	this->health = 0;

	this->currentRecoil = 0;

	this->firedThisTick = false;
	this->firedLastTick = false;
	this->changedWeaponThisTick = false;
	this->changedWeaponLastTick = false;


	this->weapon.clear();
	this->ammoLeft.clear();
	this->fireTimer = 0;
	this->reloadTimer = 0;

	this->xVel = 0;// -1 = left 0 = none 1 = right
	this->yVel = 0;// -1 = up 0 = none 1 = down

	this->baseMovementVel = 4;
	this->dodgeVel = 24;
	this->dodgeVelDrop = 2;

	this->currentMovementVel = this->baseMovementVel;

	this->dodgesLeft = 3;
	this->totalDodges = 3;
	this->dodgeBaseRechargeTime = 120;
	this->dodgeChargeTimer = 0;
}

void Player::CalculateDirectionFacing()
{
	this->directionFacing = static_cast <float> (GetAngleAsDegrees(this->location.x, this->location.y, this->target.x, this->target.y));
	this->directionFacing += 90;
}

// Logic for the player firing their weapon.
void Player::FireWeapon()
{
	// If the user is holding the fire button check if we can continue to shoot.
	if (this->weapon[this->selectedWeapon]->fireType == FireType::SemiAuto)
		if (this->firedLastTick)
		{
			this->firedThisTick = true;
			return;
		}

	if (this->weapon.size() > 0)
		if (this->weapon[this->selectedWeapon] != nullptr)
			if (this->ammoLeft[this->selectedWeapon] > 0)
			{
				if (this->weapon[this->selectedWeapon]->reloadType == ReloadType::Single && this->reloadTimer > 0)
				{
					this->reloadTimer = 0;
					this->fireTimer = this->weapon[this->selectedWeapon]->fireRate;
					return;
				}

				if (this->reloadTimer == 0 && this->fireTimer == 0)
				{
					// Get the point of the player.
					Vector2D plPoint{ round(this->location.x), round(this->location.y) };

					int tempProjectilesToLaunch = this->weapon[this->selectedWeapon]->bulletsPerShot;

					float calcDeviation = 0.0;

					while (tempProjectilesToLaunch > 0)
					{
						SDL_Point tempPoint = GetMapCoordFromCursor();

						Vector2D aimLoc = Vector2D(static_cast <float> (tempPoint.x), static_cast <float>  (tempPoint.y));

						// Calculate deviation/recoil etc.
						calcDeviation = this->weapon[this->selectedWeapon]->deviation + currentRecoil;

						float randomDeviationX = RandomFloat(-(calcDeviation / 2), calcDeviation / 2);
						float randomDeviationY = RandomFloat(-(calcDeviation / 2), calcDeviation / 2);

						aimLoc.x += static_cast<int> (round(randomDeviationX));
						aimLoc.y += static_cast<int> (round(randomDeviationY));

						// Create the projectile.
						allProjectiles.CreateProjectile(plPoint, aimLoc, this->weapon[this->selectedWeapon], this);

						tempProjectilesToLaunch--;
					}

					this->currentRecoil += this->weapon[this->selectedWeapon]->recoil;
					if (currentRecoil > this->weapon[this->selectedWeapon]->maxDeviation)
						currentRecoil = this->weapon[this->selectedWeapon]->maxDeviation;

					this->fireTimer = this->weapon[this->selectedWeapon]->fireRate;

					this->ammoLeft[this->selectedWeapon]--;

					this->firedThisTick = true;

					this->weapon[this->selectedWeapon]->PlayFireSound();
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

	SDL_Point mouse = iManager->GetMouseLocation();


	if (this->weapon.size() > 0)
	{
		float tempRecoil = (this->currentRecoil + this->weapon[this->selectedWeapon]->deviation) / 2;
		if (((this->currentRecoil + this->weapon[this->selectedWeapon]->deviation) / 2) > 0)
		{
			aimer.texture = allTextures.GetTexture("AimMarkerTop");
			aimer.location.x = static_cast<float> (mouse.x);
			aimer.location.y = static_cast<float> (mouse.y) - tempRecoil - static_cast<float> (aimer.texture->Rect().h);
			aimer.Render(0);

			aimer.texture = allTextures.GetTexture("AimMarkerBottom");
			aimer.location.x = static_cast<float> (mouse.x);
			aimer.location.y = static_cast<float> (mouse.y) + tempRecoil + static_cast<float> (aimer.texture->Rect().h) - 1;
			aimer.Render(0);

			aimer.texture = allTextures.GetTexture("AimMarkerLeft");
			aimer.location.x = static_cast<float> (mouse.x) - tempRecoil - static_cast<float> (aimer.texture->Rect().w);
			aimer.location.y = static_cast<float> (mouse.y);
			aimer.Render(0);

			aimer.texture = allTextures.GetTexture("AimMarkerRight");
			aimer.location.x = static_cast<float> (mouse.x) + tempRecoil + static_cast<float> (aimer.texture->Rect().w) - 1;
			aimer.location.y = static_cast<float> (mouse.y);
			aimer.Render(0);
		}
	}

	aimer.texture = allTextures.GetTexture("RedDot");
	aimer.location.x = static_cast<float> (mouse.x);
	aimer.location.y = static_cast<float> (mouse.y);
	aimer.Render(0);
}

void Player::DrawUIForThisPlayer()
{
	// Render the ammo count.
	if (this->weapon.size() <= 0)
		ttfAmmo.SetText("Ammo: 0");
	else if (this->reloadTimer == 0)
		ttfAmmo.SetText("Ammo: " + std::to_string(this->ammoLeft[this->selectedWeapon]));
	else
		ttfAmmo.SetText("Ammo: " + std::to_string(this->ammoLeft[this->selectedWeapon]) + " Reloading");

	ttfAmmo.Draw();

	// Render the weapon name.
	if (this->weapon.size() > 0)
		ttfWeapon.SetText("Weapon: " + this->weapon[this->selectedWeapon]->name);
	else
		ttfWeapon.SetText("Weapon: Unarmed");

	ttfWeapon.Draw();

	// Render the dodges count.
	ttfDodges.SetText("Dodges: " + std::to_string(this->dodgesLeft));
	ttfDodges.Draw();	
}

void Player::Dodge()
{
	// Stop palyer from dodging if they have no dodge charges.
	if (this->dodgesLeft <= 0)
		return;

	// Player must let go of key before they can dodge again.
	if (this->dodgedLastTick)
	{
		this->dodgedThisTick = true;
		return;
	}

	this->currentMovementVel = this->dodgeVel;
	this->dodgesLeft--;
	this->dodgedThisTick = true;

	allSounds.GetSound("Dodge")->Play();
}

void Player::AddWeapon(Weapon* wep)
{
	this->weapon.push_back(wep);
	this->ammoLeft.push_back(wep->totalAmmo);
}

void Player::RemoveWeapon(int weaponIndex)
{
	this->weapon.erase(this->weapon.begin() + weaponIndex);
	this->SwitchToLastWeapon();
}

void Player::SwitchToNextWeapon()
{
	// If the user is holding the button stop it from continuously cycling weapons.
	if (this->changedWeaponLastTick)
	{
		this->changedWeaponThisTick = true;
		return;
	}

	if (this->weapon.size() > 0)
	{
		this->selectedWeapon++;
		if (this->selectedWeapon >= this->weapon.size())
			this->selectedWeapon = 0;

		this->fireTimer = this->weapon[this->selectedWeapon]->fireRate;
		this->reloadTimer = 0;

		this->changedWeaponThisTick = true;
	}
}

void Player::SwitchToLastWeapon()
{
	// If the user is holding the button stop it from continuously cycling weapons.
	if (this->changedWeaponLastTick)
	{
		this->changedWeaponThisTick = true;
		return;
	}

	if (this->weapon.size() > 0)
	{
		this->selectedWeapon--;
		if (this->selectedWeapon < 0)
			this->selectedWeapon = static_cast<int>(this->weapon.size()) - 1;

		this->fireTimer = this->weapon[this->selectedWeapon]->fireRate;
		this->reloadTimer = 0;

		this->changedWeaponThisTick = true;
	}
}

// Start making the player reload their weapon.
void Player::ReloadWeapon()
{
	if (this->weapon.size() > 0)
		if (this->ammoLeft[this->selectedWeapon] < this->weapon[this->selectedWeapon]->totalAmmo)
			if (this->reloadTimer == 0)
			{
				this->reloadTimer = this->weapon[this->selectedWeapon]->reloadTime;
				this->fireTimer = this->weapon[this->selectedWeapon]->fireRate;
			}
}


void Player::HandleEvents()
{
	// Reloading logic.
	if (this->reloadTimer > 0)
	{
		this->reloadTimer--;
		if (this->reloadTimer == 0)
			switch (this->weapon[this->selectedWeapon]->reloadType)
			{
			case ReloadType::Clip:
				this->ammoLeft[this->selectedWeapon] = this->weapon[this->selectedWeapon]->totalAmmo;
				break;

			case ReloadType::Single:
				if (this->ammoLeft[this->selectedWeapon] < this->weapon[this->selectedWeapon]->totalAmmo)
				{
					this->ammoLeft[this->selectedWeapon]++;
					this->reloadTimer = this->weapon[this->selectedWeapon]->reloadTime;
				}
				break;
			}
	}

	// Reduce the fire timer each tick so that weapons fire when required.
	if (this->fireTimer > 0 && this->reloadTimer == 0)
		this->fireTimer--;

	if (this->currentRecoil > 0/* && !this->isFiring && this->fireTimer == 0*/)
	{
		this->currentRecoil -= this->weapon[this->selectedWeapon]->recoilControlRate;

		if (this->currentRecoil < 0)
			this->currentRecoil = 0;
	}

	// dodging logic.
	if (this->currentMovementVel > this->baseMovementVel)
	{
		this->currentMovementVel -= this->dodgeVelDrop;
		if (this->currentMovementVel < this->baseMovementVel)
			this->currentMovementVel = this->baseMovementVel;
	}

	if (this->dodgesLeft < this->totalDodges)
	{
		this->dodgeChargeTimer++;

		if (this->dodgeChargeTimer >= this->dodgeBaseRechargeTime)
		{
			this->dodgesLeft++;
			this->dodgeChargeTimer = 0;
		}
	}

	// Reset is firing to false each frame.
	// Each time the user fires it will set this to true.
	this->firedLastTick = this->firedThisTick;
	this->firedThisTick = false;
	this->changedWeaponLastTick = this->changedWeaponThisTick;
	this->changedWeaponThisTick = false;
	this->dodgedLastTick = this->dodgedThisTick;
	this->dodgedThisTick = false;
	if (currentPlayer == this)
	{
		SDL_Point point = GetMapCoordFromCursor();
		Vector2D vec { static_cast <float> (point.x) , static_cast <float> (point.y)};
		this->target = vec;
		this->CalculateDirectionFacing();
	}		
}

Player* Players::CreatePlayer(std::string playerName)
{
	Player* pl = new Player();

	pl->name = playerName;

	this->playerList.push_back(pl);

	debug.Log("Character", "CreatePlayer", "Created a player of name: " + playerName);

	return this->playerList.back();
}

void Players::DeletePlayer(std::string playerName)
{
	int i = 0;

	for (Player* pl : playerList)
	{
		if (pl->name == playerName)
		{
			playerList.erase(playerList.begin() + i);
			delete pl;
			debug.Log("Character", "DeletePlayer", "Deleted a player of name: " + playerName);
			return;
		}

		i++;
	}

	debug.Log("Projectile", "DestroyProjectile", "Call to destroy a player of name: " + playerName + " has failed!");
}

void Players::DeleteAllPlayers()
{
	int i = 0;

	for (int i = 0; i < playerList.size(); i++)
	{
		Player* pl = playerList[i];
		playerList.erase(playerList.begin());
		delete pl;
	}

	debug.Log("Players", "DeleteAllPlayers", "Deleted all players");
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
		pl->HandleEvents();
}