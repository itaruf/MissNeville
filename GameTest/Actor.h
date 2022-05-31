#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include "Vector2D.h"
class Collision;
#include "Collision.h"
#include "App/SimpleSprite.h"
class Scene;
#include "Scene.h"
#include <memory>
#include "EDirection.h"
#include "EMobility.h"

// Base class for all physical entities in the game (props, characters (player, NPC), ...) 
class Actor
{
protected:
	static constexpr Mobility defaultMobility{ Mobility::STATIC };
	static constexpr Direction defaultDirection{ Direction::STILL };

	std::string name;
	CSimpleSprite* sprite;
	Vector2D* position;
	Collision* collider;
	Mobility mobility = defaultMobility;
	Direction direction = defaultDirection;
public:
	Actor(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	Actor(Actor* actor);
	virtual ~Actor();

	const std::string& GetName() const;
	CSimpleSprite* GetSprite();
	Vector2D* GetPosition();
	Collision* GetCollider();
	const Mobility& GetMobility();
	const Direction& GetDirection();

	void SetName(std::string name);
	void SetSprite(CSimpleSprite* sprite);
	void SetSprite(CSimpleSprite& sprite);
	void SetPosition(Vector2D* position);
	void SetPosition(float x = 0, float y = 0);
	void SetCollider(Collision* collider);
};

#endif

