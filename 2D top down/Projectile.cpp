#include "Projectile.h"
#include "Math functions.h"
#include "Map Data Type.h"
#include "globals.h"

Projectile::Projectile()
{
	this->type = PROJECTILETYPE_BULLET;
	this->damage = 0;
	this->Owner = nullptr;
}

bool Projectile::CalcProjectile()
{
	double tempXDist = this->xLoc - this->targetPoint.x;
	double tempYDist = this->yLoc - this->targetPoint.y;
	double distance = sqrt((tempXDist * tempXDist) + (tempYDist * tempYDist));

	if (distance > 1)
	{
		float oldXLoc = this->xLoc;
		float oldYLoc = this->yLoc;

		double xDistance = this->xStart - this->targetPoint.x;
		double yDistance = this->yStart - this->targetPoint.y;

		this->xLoc -= xDistance * this->velocity;
		this->yLoc -= yDistance * this->velocity;

		// Get all points we have passed and cause damage as needed.
		std::vector<SDL_Point> points = GetAllMapDataBetweenPoints(oldXLoc, oldYLoc, xLoc, yLoc);

		if (points.size() > 0)
			for (auto& point : points)
				if (map.GetTypeAt(point.x, point.y) != MAPDATATYPE_EMPTY)
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
						currentMapDataType = MAPDATATYPE_EMPTY;
					}

					map.SetDataAt(point.x, point.y, currentMapDataType, currentHealth);

					// Check if the bullet is out of potential damage.
					if (this->damage <= 0)					
						return false;					
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
	else
		return false;

	return true;
}

Projectile* Projectiles::CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon, Player* owner)
{
	Projectile* proj = new Projectile();

	proj->Owner = owner;

	proj->xLoc = static_cast<float> (start.x);
	proj->yLoc = static_cast<float> (start.y);

	proj->xStart = start.x;
	proj->yStart = start.y;
	proj->targetPoint = end;

	proj->directionFacing = static_cast<float> (GetAngleAsDegrees(start.x, start.y, proj->targetPoint.x, proj->targetPoint.y));

	// TODO: automate texture and velocity
	proj->texture = allTextures.GetTexture("Bullet");
	// TODO

	proj->velocity = weapon->projectileSpeed;

	proj->damage = weapon->damage;	

	this->projectileList.push_back(proj);

	debug.Log("Projectile", "CreateProjectile", "Created a Projectile start point x/y " + std::to_string(proj->xLoc) + "/" + std::to_string(proj->yLoc) + " going angle: " + std::to_string(proj->directionFacing) + " Target of: " + std::to_string(end.x) + "/" + std::to_string(end.y));

	return this->projectileList.back();
}

void Projectiles::DestroyProjectile(Projectile* proj)
{
	int i = 0;

	for (Projectile* listProj : this->projectileList)
	{
		if (listProj == proj)
		{
			debug.Log("Projectile", "DestroyProjectile", "Deleted a projectile at: " + std::to_string(listProj->xLoc) + "/" + std::to_string(listProj->yLoc));
			this->projectileList.erase(this->projectileList.begin() + i);			
			return;
		}

		i++;
	}

	debug.Log("Projectile", "DestroyProjectile", "Call to destroy a projectile has failed!");
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