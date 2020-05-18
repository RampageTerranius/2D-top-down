#include "Projectile.h"
#include "Math functions.h"
#include "Map Data Type.h"
#include "globals.h"

Projectile::Projectile()
{
	this->type = ProjectileType::Bullet;
	this->damage = 0;
	this->Owner = nullptr;
	this->targetPoint = SDL_Point{ 0, 0 };
	this->xStart = 0.0;
	this->yStart = 0.0;
}

bool Projectile::CalcProjectile()
{	
	{
		float oldXLoc = this->xLoc;
		float oldYLoc = this->yLoc;

		float distance = sqrt(pow(this->targetPoint.x - this->xStart, 2) + pow(this->targetPoint.y - this->yStart, 2));
		float directionX = (this->targetPoint.x - this->xStart) / distance;
		float directionY = (this->targetPoint.y - this->yStart) / distance;

		this->xLoc += directionX * this->velocity;
		this->yLoc += directionY * this->velocity;

		// Get all points we have passed and cause damage as needed.
		std::vector<SDL_Point> points = GetAllMapDataBetweenPoints(static_cast<int> (oldXLoc), static_cast<int> (oldYLoc), static_cast<int> (xLoc), static_cast<int> (yLoc));

		if (points.size() > 0)
			for (auto& point : points)
			{
				if (map.GetTypeAt(point.x, point.y) != MapDataType::Empty)
				{
					int currentHealth = map.GetHealthAt(point.x, point.y);
					MapDataType currentMapDataType = map.GetTypeAt(point.x, point.y);

					int tempDamage = this->damage;

					this->damage -= currentHealth;
					currentHealth -= tempDamage;

					// Check if the current block should be destroyed.
					if (currentHealth <= 0)
					{
						currentHealth = 0;
						currentMapDataType = MapDataType::Empty;
					}

					map.SetDataAt(point.x, point.y, currentMapDataType, currentHealth);

					// Check if the bullet is out of potential damage.
					if (this->damage <= 0)
						return false;
				}

				float currDistance = sqrt(pow(this->xLoc - this->xStart, 2) + pow(this->yLoc - this->yStart, 2));

				if (currDistance >= distance)
				{
					this->xLoc = static_cast<float> (this->targetPoint.x);
					this->yLoc = static_cast<float> (this->targetPoint.y);
					return false;
				}
			}

		// Check if bullet has hit the edge of the map.
		if (this->xLoc < 0)
			return false;
		else if (this->yLoc < 0)
			return false;
		else if (this->xLoc >= map.GetSizeX())
			return false;
		else if (this->yLoc >= map.GetSizeY())
			return false;
	}

	return true;
}

void Projectiles::CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon, Player* owner)
{	
	Projectile* proj = new Projectile();

	proj->Owner = owner;

	proj->xLoc = static_cast<float> (start.x);
	proj->yLoc = static_cast<float> (start.y);

	// Get the start and ending points.
	proj->xStart = static_cast<float> (start.x);
	proj->yStart = static_cast<float> (start.y);
	proj->targetPoint = end;

	proj->directionFacing = static_cast<float> (GetAngle(start.x, start.y, proj->targetPoint.x, proj->targetPoint.y));

	// TODO: automate texture
	proj->texture = allTextures.GetTexture("Bullet");
	// TODO

	proj->velocity = weapon->projectileSpeed;

	proj->damage = weapon->damage;

	this->projectileList.push_back(proj);

	debug.Log("Projectiles", "CreateProjectile", "Created a Projectile start point x/y " + std::to_string(proj->xLoc) + "/" + std::to_string(proj->yLoc) + " going angle: " + std::to_string(proj->directionFacing) + " Target of: " + std::to_string(end.x) + "/" + std::to_string(end.y));
}

void Projectiles::DestroyProjectile(Projectile* proj)
{
	int i = 0;

	for (auto& listProj : this->projectileList)
	{
		if (listProj == proj)
		{
			debug.Log("Projectiles", "DestroyProjectile", "Deleted a projectile at: " + std::to_string(listProj->xLoc) + "/" + std::to_string(listProj->yLoc));
			this->projectileList.erase(this->projectileList.begin() + i);			
			return;
		}

		i++;
	}

	debug.Log("Projectiles", "DestroyProjectile", "Call to destroy a projectile has failed!");
}

void Projectiles::DestroyAllProjectiles()
{
	int i = 0;

	for (Projectile* listProj : this->projectileList)
	{
		this->projectileList.erase(this->projectileList.begin() + i);
		delete listProj;

		i++;
	}

	debug.Log("Projectiles", "DestroyAllProjectiles", "Destroyed all projectiles");
}

void Projectiles::CalcAllProjectiles()
{
	for (auto& projectile : this->projectileList)	
		if (!projectile->CalcProjectile())
			allProjectiles.DestroyProjectile(projectile);	
}

void Projectiles::RenderAllProjectiles()
{
	for (auto& projectile : this->projectileList)
		projectile->Render();
}