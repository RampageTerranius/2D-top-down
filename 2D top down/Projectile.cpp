#include "Projectile.h"
#include "Math functions.h"
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
	while (distanceLeft > 0)
	{
		float i = static_cast<float> (cos(directionFacing * M_PI / 180) * velocity);
		float n = static_cast<float> (sin(directionFacing * M_PI / 180) * velocity);

		xLoc += i;
		yLoc += n;

		if (xLoc < 0)
		{
			xLoc = 0;
			distanceLeft = 0;
			break;
		}

		if (yLoc < 0)
		{
			yLoc = 0;
			distanceLeft = 0;
			break;
		}

		if (xLoc >= map.GetSizeX())
		{
			xLoc = static_cast<float> (map.GetSizeX() - 1);
			distanceLeft = 0;
			break;
		}

		if (yLoc >= map.GetSizeY())
		{
			yLoc = static_cast<float> (map.GetSizeY() - 1);
			distanceLeft = 0;
			break;
		}

		if (map.GetDataAt(xLoc, yLoc) != MAPDATATYPE_EMPTY)
		{
			// TODO: map calc here
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

	projectileList.push_back(proj);

	debug.Log("Projectile", "CreateProjectile", "Created a Projectile start point x/y " + std::to_string(proj->xLoc) + "/" + std::to_string(proj->yLoc) + " going angle: " + std::to_string(proj->directionFacing) + " Distance of: " + std::to_string(proj->distanceLeft));

	return projectileList.back();
}

void Projectiles::DestroyProjectile(Projectile* proj)
{
	int i = 0;

	for (Projectile* listProj : projectileList)
	{
		if (listProj == proj)
		{
			projectileList.erase(projectileList.begin() + i);
			debug.Log("Projectile", "DestroyProjectile", "Deleted a projectile");
			return;
		}

		i++;
	}

	debug.Log("Projectile", "DestroyProjectile", "Call to destroy a projectile has failed!");
}

void Projectiles::CalcAllProjectiles()
{
	for (auto& projectile : projectileList)
		projectile->CalcProjectile();
}

void Projectiles::RenderAllProjectiles()
{
	for (auto& projectile : projectileList)
		projectile->Render();
}