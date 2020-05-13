#include "Projectile.h"
#include "Math functions.h"
#include "Map Data Type.h"
#include "globals.h"

Projectile::Projectile()
{
	this->type = PROJECTILETYPE_BULLET;
	this->distanceLeft = 0;
	this->damage = 0;
	this->Owner = nullptr;
}

void Projectile::CalcProjectile()
{	
	float i = static_cast<float> (cos(this->directionFacing * M_PI / 180) * this->velocity);
	float n = static_cast<float> (sin(this->directionFacing * M_PI / 180) * this->velocity);

	float oldXLoc = this->xLoc;
	float oldYLoc = this->yLoc;

	this->xLoc += i;
	this->yLoc += n;

	// Reduce the total distance by how much the bullet has moved.
	if (i < 0)
		this->distanceLeft += i;
	else
		this->distanceLeft -= i;
	if (n < 0)
		this->distanceLeft += n;
	else
		this->distanceLeft -= n;

	// Check if bullet has hit the edge of the map.
	if (this->xLoc < 0)
		this->distanceLeft = 0;	
	else if (this->yLoc < 0)
		this->distanceLeft = 0;	
	else if (this->xLoc >= map.GetSizeX())	
		this->distanceLeft = 0;	
	else if (this->yLoc >= map.GetSizeY())
		this->distanceLeft = 0;	

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
				{
					this->distanceLeft = 0;
					break;
				}
			}
}

Projectile* Projectiles::CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon, Player* owner)
{
	Projectile* proj = new Projectile();

	proj->Owner = owner;

	proj->xLoc = static_cast<float> (start.x);
	proj->yLoc = static_cast<float> (start.y);

	proj->directionFacing = static_cast<float> (GetAngleAsDegrees(start.x, start.y, end.x, end.y));

	// TODO: automate texture and velocity
	proj->texture = allTextures.GetTexture("Bullet");
	// TODO

	proj->velocity = weapon->projectileSpeed;
	proj->distanceLeft = static_cast<float> (GetDistance(start.x, start.y, end.x, end.y));
	if (proj->distanceLeft > static_cast<float> (weapon->projectileDistance))
		proj->distanceLeft = static_cast<float> (weapon->projectileDistance);

	proj->damage = weapon->damage;

	this->projectileList.push_back(proj);

	debug.Log("Projectile", "CreateProjectile", "Created a Projectile start point x/y " + std::to_string(proj->xLoc) + "/" + std::to_string(proj->yLoc) + " going angle: " + std::to_string(proj->directionFacing) + " Distance of: " + std::to_string(proj->distanceLeft));

	return this->projectileList.back();
}

void Projectiles::DestroyProjectile(Projectile* proj)
{
	int i = 0;

	for (Projectile* listProj : this->projectileList)
	{
		if (listProj == proj)
		{
			this->projectileList.erase(this->projectileList.begin() + i);
			debug.Log("Projectile", "DestroyProjectile", "Deleted a projectile");
			return;
		}

		i++;
	}

	debug.Log("Projectile", "DestroyProjectile", "Call to destroy a projectile has failed!");
}

void Projectiles::CalcAllProjectiles()
{
	for (auto& projectile : this->projectileList)
	{
		projectile->CalcProjectile();	
		if (projectile->distanceLeft <= 0)
			allProjectiles.DestroyProjectile(projectile);
	}
}

void Projectiles::RenderAllProjectiles()
{
	for (auto& projectile : this->projectileList)
		projectile->Render();
}