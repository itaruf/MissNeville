#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "../../../App/app.h"

//#include "../../Actors/Actor.h"
//#include "../../Actors/Collectibles/Collectable.h"
#include "../../Enums/EDirection.h"
#include "../../Enums/ECollider.h"
#include "../../Utilities/Maths/Vector2D.h"

class Actor;
class Collectable;
// Class which defines the collision of an actor
class Collision
{
public:
	ColliderType _colliderType;
	float _height;
	float _width;
	Vector2D _offset;
public:
	Collision();
	Collision(float height = 32, float width = 32, ColliderType colliderType = ColliderType::Block, Vector2D offset = Vector2D(0,0));
	~Collision();

	const float& GetHeight() const;
	const float& GetWidth() const;

	void SetHeight(float value);
	void SetWidth(float value);
	
	bool isColliding(Actor* actor, Actor* other, float x, float y);
	bool isOverlapping(Actor* actor, Actor* other);

	void DrawCollision(Actor* actor, float r, float g, float b);
};

#endif