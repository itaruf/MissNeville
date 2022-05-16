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
#include "EMobility.h"

class Actor
{
protected:
	static constexpr Mobility defaultMobility = Mobility::STATIC;
	static constexpr Direction defaultDirection = Direction::STILL;

	std::string name;
	CSimpleSprite* sprite;
	Vector2D* position;
	Collision* collider;
	Room* currentRoom;
	Mobility mobility = defaultMobility;
	Direction direction = defaultDirection;
public:
	Actor(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom);
	Actor(Actor* actor);
	~Actor();

	const std::string& GetName() const;
	CSimpleSprite* GetSprite();
	Vector2D* GetPosition();
	Collision* GetCollider();
	Room* GetCurrentRoom();
	const Mobility& GetMobility();
	const Direction& GetDirection();
	Vector2D* GetForwardVector();
	Vector2D* GetRightVector();

	void SetName(std::string name);
	void SetSprite(CSimpleSprite* sprite);
	void SetSprite(CSimpleSprite& sprite);
	void SetPosition(Vector2D* position);
	void SetPosition(float x = 0, float y = 0);
	void SetCollider(Collision* collider);
	void SetCurrentRoom(Room* room);
};

#endif

