#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "EDirection.h"
class Actor;
#include "Actor.h"

class Collision
{
public:
	enum class ColliderType {
		Block,
		Overlap,
	};

	ColliderType colliderType;
	float height;
	float width;

	Collision(ColliderType colliderType, float height, float width);
	~Collision() {}

	bool isColliding(Actor* character, Actor*& other, float x, float y);
	float& GetHeight();
	void SetHeight(float value);
	float& GetWidth();
	void SetWidth(float value);
};

#endif

