#pragma once

#include <string>

class Vector2D
{
public:
	Vector2D(float newX, float newY);

	Vector2D& Add(Vector2D& vec);
	Vector2D& Subtract(Vector2D& vec);
	Vector2D& Multiply(Vector2D& vec);
	Vector2D& Divide(Vector2D& vec);	

	friend Vector2D& operator+(Vector2D& vec1, Vector2D& vec2);
	friend Vector2D& operator-(Vector2D& vec1, Vector2D& vec2);
	friend Vector2D& operator*(Vector2D& vec1, Vector2D& vec2);
	friend Vector2D& operator/(Vector2D& vec1, Vector2D& vec2);

	Vector2D& operator+=(Vector2D& vec);
	Vector2D& operator-=(Vector2D& vec);
	Vector2D& operator*=(Vector2D& vec);
	Vector2D& operator/=(Vector2D& vec);

	std::string ToString();

	float x = 0.0f;
	float y = 0.0f;
};