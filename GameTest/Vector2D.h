
#pragma once
#ifndef VECTOR2D_H_
#define VECTOR2D_H_

// Class which defines the x and y position of an actor 
class Vector2D
{
public:
	float _x;
	float _y;

	Vector2D(float x = 0, float y = 0);
	~Vector2D() = default;
};

#endif
