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
	this->target = Vector2D{ 0, 0 };
	this->start = Vector2D{ 0, 0 };
	this->maxDistance = 0;
}

bool Projectile::CalcProjectile()
{	
	float oldXLoc = this->loc.x;
	float oldYLoc = this->loc.y;

	float distance = sqrt(pow(this->target.x - this->start.x, 2) + pow(this->target.y - this->start.y, 2));
	if (distance > this->maxDistance)
		distance = static_cast <float> (this->maxDistance);

	Vector2D diffVec(this->target.x - this->start.x, this->target.y - this->start.y);
	diffVec.Normalize();
	diffVec.Multiply(this->velocity);

	this->loc.x += diffVec.x;
	this->loc.y += diffVec.y; 

	// Get all points we have passed and cause damage as needed.
	std::vector<SDL_Point> points = GetAllMapDataBetweenPoints(static_cast<int> (oldXLoc), static_cast<int> (oldYLoc), static_cast<int> (this->loc.x), static_cast<int> (this->loc.y));

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

			float currDistance = sqrt(pow(point.x - this->start.x, 2) + pow(point.y - this->start.y, 2));

			if (currDistance >= distance)
				return false;
		}

	// Check if bullet has hit the edge of the map.
	if (this->loc.x < 0)
		return false;
	else if (this->loc.y < 0)
		return false;
	else if (this->loc.x >= map.GetSizeX())
		return false;
	else if (this->loc.y >= map.GetSizeY())
		return false;

	return true;
}

void Projectiles::CreateProjectile(Vector2D start, Vector2D end, Weapon* weapon, Player* owner)
{	
	Projectile* proj = new Projectile();

	proj->Owner = owner;

	proj->loc = start;

	// Get the start and ending points.
	proj->start = proj->loc;
	proj->target = end;

	proj->texture = allTextures.GetTexture("Bullet");

	proj->velocity = weapon->projectileSpeed;

	proj->damage = weapon->damage;

	proj->maxDistance = weapon->projectileDistance;

	this->projectileList.PushBack(proj);

	if (this->debugProjectiles)
		debug.Log("Projectiles", "CreateProjectile", "Created a Projectile start point x/y " + proj->start.ToString() + " going to: " + proj->target.ToString() + " Deviation of: " + std::to_string(proj->Owner->weapon[proj->Owner->selectedWeapon]->deviation));
}

void Projectiles::DestroyProjectile(Projectile* proj)
{
	float x = proj->loc.x;
	float y = proj->loc.y;

	bool deleteResult = this->projectileList.Delete(proj);

	if (this->debugProjectiles)
		if (deleteResult)
			debug.Log("Projectiles", "DestroyProjectile", "Deleted a projectile at " + std::to_string(x) + "/" + std::to_string(y));
		else
			debug.Log("Projectiles", "DestroyProjectile", "Failed to delete projectile!");
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