#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "app\app.h"
#include "EDirection.h"

class Actor;
#include "Actor.h"

// Class which defines the collision of an actor
class Collision
{
public:
	enum class ColliderType {
		Block,
		Overlap,
	};

	ColliderType _colliderType;
	float _height;
	float _width;
	Vector2D* _offset;

	Collision();
	Collision(float height = 32, float width = 32, ColliderType colliderType = ColliderType::Block, Vector2D* offset = new Vector2D(0,0));

	~Collision();

	const float& GetHeight() const;
	const float& GetWidth() const;
	bool isColliding(Actor* actor, Actor* other, float x, float y);

	void SetHeight(float value);
	void SetWidth(float value);

	void DrawCollision(Actor* actor, float r, float g, float b);

	//Vector2D* GetDownLeftColPos(Actor* actor);
	//Vector2D* GetDownRightColPos(Actor* actor);
	//Vector2D* GetUpLeftColPos(Actor* actor);
	//Vector2D* GetUpRightColPos(Actor* actor);

};

#endif

