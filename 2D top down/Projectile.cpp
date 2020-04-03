#include "Projectile.h"
#include "Math functions.h"
#include "globals.h"

bool Projectile::CalcProjectile()
{
	MoveObjectAccoringToVel();

	distanceLeft -= velocity;

	if (distanceLeft <= 0)
	{
		debug.Log("Projectile", "CalcProjectile", "Projectile is end of life");
		return false;
	}

	return true;
}

Projectile* Projectiles::CreateProjectile(SDL_Point start, SDL_Point end, Weapon* weapon)
{
	Projectile* proj = new Projectile();

	proj->xLoc = (float)start.x;
	proj->yLoc = (float)start.y;

	proj->directionFacing = (float)GetAngleAsDegrees(start.x, start.y, end.x, end.y);

	// TODO: automate texture and velocity
	proj->texture = allTextures.GetTexture("Bullet");
	// TODO

	proj->velocity = weapon->projectileSpeed;
	proj->distanceLeft = (float)GetDistance(start.x, start.y, end.x, end.y);
	if (proj->distanceLeft > (float)weapon->projectileDistance)
		proj->distanceLeft = (float)weapon->projectileDistance;

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
		if (!projectile->CalcProjectile())
			allProjectiles.DestroyProjectile(projectile);
}

void Projectiles::RenderAllProjectiles()
{
	for (auto& projectile : projectileList)
		projectile->Render();
}