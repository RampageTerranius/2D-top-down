#include "Projectile.h"
#include "Math functions.h"
#include "Map Data Type.h"
#include "globals.h"

void ProjectileLinkedList::PushBack(Projectile* data)
{
	// No front.
	if (this->front == nullptr)
	{
		this->front = data;
		this->count++;
	}
	// No back.
	else if (this->back == nullptr)
	{
		this->back = data;
		this->back->last = this->front;
		this->front->next = this->back;
		this->count++;
	}
	// A front and a back.
	else
	{
		Projectile* tempBack = this->back;
		this->back = data;
		this->back->last = tempBack;
		tempBack->next = data;
		this->count++;
	}
}

bool ProjectileLinkedList::DeleteBack()
{
	if (this->back == nullptr)
		return false;

	Projectile* tempProj = this->back;

	if (this->back->last == this->front)
	{
		this->back = nullptr;
		this->front->next = nullptr;
	}
	else
	{
		this->back = this->back->last;
		this->back->next = nullptr;
	}

	delete tempProj;

	this->count--;

	return true;
}

bool ProjectileLinkedList::DeleteFront()
{
	if (this->front == nullptr)
		return false;

	Projectile* tempProj = this->front;
	
	if (this->back != nullptr && this->front->next == this->back)
	{
		this->back->last = nullptr;
		this->front = this->back;
		this->back = nullptr;
	}
	else
	{
		this->front = this->front->next;
		if (this->front != nullptr)
			this->front->last = nullptr;
	}	

	delete tempProj;

	this->count--;

	return true;
}

bool ProjectileLinkedList::Delete(Projectile* data)
{
	if (this->front == data)
		return DeleteFront();	
	
	if (this->back == data)
		return DeleteBack();	

	Projectile* last = data->last;
	Projectile* next = data->next;
	last->next = next;
	next->last = last;

	delete data;

	this->count--;

	return true;
}

void ProjectileLinkedList::Clear()
{
	// Clear all data out of the linked list.
	while (this->front != nullptr)
	{
		Projectile* delData;

		delData = this->front;
		this->front = this->front->next;

		delete delData;
		this->count--;
	}
}

Projectile::Projectile()
{
	this->type = ProjectileType::Bullet;
	this->damage = 0;
	this->Owner = nullptr;
	this->targetPoint = SDL_Point{ 0, 0 };
	this->xStart = 0.0;
	this->yStart = 0.0;
	this->maxDistance = 0;
}

bool Projectile::CalcProjectile()
{	
	float oldXLoc = this->xLoc;
	float oldYLoc = this->yLoc;

	float distance = sqrt(pow(this->targetPoint.x - this->xStart, 2) + pow(this->targetPoint.y - this->yStart, 2));
	if (distance > this->maxDistance)
		distance = this->maxDistance;

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

	proj->maxDistance = weapon->projectileDistance;

	this->projectileList.PushBack(proj);

	debug.Log("Projectiles", "CreateProjectile", "Created a Projectile start point x/y " + std::to_string(proj->xLoc) + "/" + std::to_string(proj->yLoc) + " going angle: " + std::to_string(proj->directionFacing) + " Target of: " + std::to_string(end.x) + "/" + std::to_string(end.y));
}

void Projectiles::DestroyProjectile(Projectile* proj)
{
	float x = proj->xLoc;
	float y = proj->yLoc;

	if (this->projectileList.Delete(proj))
		debug.Log("Projectiles", "DestroyProjectile", "Deleted a projectile at " + std::to_string(x) + "/" + std::to_string(y));
	else
		debug.Log("Projectiles", "DestroyProjectile", "Faield to delete projectile!");
}

void Projectiles::DestroyAllProjectiles()
{
	Projectile* data = projectileList.front;

	while (data != nullptr)
	{
		Projectile* tempData = data->next;
		DestroyProjectile(data);
		data = tempData;
	}

	debug.Log("Projectiles", "DestroyAllProjectiles", "Destroyed all projectiles");
}

void Projectiles::CalcAllProjectiles()
{
	Projectile* data = projectileList.front;

	while (data != nullptr)
	{
		if (data->CalcProjectile())
			data = data->next;
		else
		{
			Projectile* tempData = data;
			data = data->next;
			allProjectiles.DestroyProjectile(tempData);
		}
	}
}

void Projectiles::RenderAllProjectiles()
{
	Projectile* data = projectileList.front;

	while (data != nullptr)
	{
		data->Render();
		data = data->next;
	}
}