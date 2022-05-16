#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_

#include "app\app.h"
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
	Vector2D* offset;

	Collision(ColliderType colliderType, float height, float width, Vector2D* offset = new Vector2D(0,0));
	~Collision() {}

	const float& GetHeight() const;
	const float& GetWidth() const;
	Vector2D* GetDownLeftColPos(Actor* actor);
	Vector2D* GetDownRightColPos(Actor* actor);
	Vector2D* GetUpLeftColPos(Actor* actor);
	Vector2D* GetUpRightColPos(Actor* actor);
	bool isColliding(Actor* actor, Actor* other, float x, float y);

	void SetHeight(float value);
	void SetWidth(float value);

	void DrawCollision(Actor* actor, float r, float g, float b);
};

#endif

