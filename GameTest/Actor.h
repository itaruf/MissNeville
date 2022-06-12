#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include "Vector2D.h"
class Collision;
#include "Collision.h"
#include "App/SimpleSprite.h"
#include <memory>
#include "EDirection.h"
#include "EMobility.h"

// Base class for all physical entities in the game (props, characters (player, NPC), ...) 
class Actor
{
protected:
	static constexpr Mobility defaultMobility{ Mobility::STATIC };
	static constexpr Direction defaultDirection{ Direction::STILL };

	std::string _tag;
	std::string _name;
	CSimpleSprite* _sprite;
	Vector2D* _position;
	Collision* _collider;
	Mobility _mobility{ defaultMobility };
	Direction _direction{ defaultDirection };

public:
	friend class PlayerController;
	friend class ObjectController;

	Actor(std::string name = " ", CSimpleSprite* sprite = nullptr, Vector2D* position = nullptr, Collision* collider = nullptr);
	Actor(Actor* actor);
	virtual ~Actor();

	const std::string& GetName() const;
	CSimpleSprite* GetSprite();
	Vector2D* GetPosition();
	Collision* GetCollider();
	const Mobility& GetMobility();
	const Direction& GetDirection();
	const std::string& GetTag();

	void SetName(std::string name);
	void SetSprite(CSimpleSprite* sprite);
	void SetSprite(CSimpleSprite& sprite);
	void SetPosition(Vector2D* position);
	void SetPosition(float x = 0, float y = 0);
	void SetCollider(Collision* collider);
	void SetDirection(Direction direction);
	void SetTag(std::string&& tag);
};

#endif

