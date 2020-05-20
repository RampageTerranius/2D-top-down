#include "Vector2D.h"

#include <string>

Vector2D::Vector2D(float newX, float newY)
{
	this->x = newX;
	this->y = newY;
}

Vector2D& Vector2D::Add(Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtract(Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& vec1, Vector2D& vec2)
{
	return vec1.Add(vec2);
}

Vector2D& operator-(Vector2D& vec1, Vector2D& vec2)
{
	return vec1.Subtract(vec2);
}

Vector2D& operator*(Vector2D& vec1, Vector2D& vec2)
{
	return vec1.Multiply(vec2);
}

Vector2D& operator/(Vector2D& vec1, Vector2D& vec2)
{
	return vec1.Divide(vec2);
}

Vector2D& Vector2D::operator+=(Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(Vector2D& vec)
{
	return this->Divide(vec);
}

std::string Vector2D::ToString()
{
	return std::to_string(this->x) + "/" + std::to_string(this->y);
}