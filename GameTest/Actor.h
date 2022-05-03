#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include "Vector2D.h"
class Collision;
#include "Collision.h"

#include "App/SimpleSprite.h"
#include "Room.h"
#include <memory>
#include "EDirection.h"

class Actor
{
protected:
	std::string name;
	CSimpleSprite* sprite;
	Vector2D position;
	Collision* collider;
	Room* currentRoom;
public:
	Direction direction = Direction::STILL;
	Actor(std::string name, CSimpleSprite*& sprite, Vector2D& position, Collision*& collider, Room* currentRoom);
	~Actor() = default;

	std::string& GetName();
	CSimpleSprite*& GetSprite();
	void SetSprite(CSimpleSprite* sprite);
	Vector2D& GetPosition();
	void SetPosition(Vector2D& position);
	void SetPosition(float x = 0, float y = 0);
	Collision*& GetCollider();
	Room*& GetCurrentRoom();
};

#endif

