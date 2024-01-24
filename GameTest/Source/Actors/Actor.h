#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include "../../App/SimpleSprite.h"

#include "../Components/Physics2D/Collision.h"
#include "../Controllers/Controller.h"
#include "../Enums/EDirection.h"
#include "../Enums/EMobility.h"
#include "../Scenes/Scene.h"
#include "../Utilities/Models.h"
#include "../Utilities/Maths/Vector2D.h"

#include <memory>
#include <unordered_map>

class Collision;
class Scene;

// Base class for all physical entities in the game (props, characters (player, NPC), ...) 
class Actor
{
protected:
	static constexpr Mobility defaultMobility{ Mobility::STATIC };
	static constexpr Direction defaultDirection{ Direction::STILL };

	std::string _tag{ "" };
	std::string _name;
	CSimpleSprite* _sprite;
	Vector2D _position;
	Collision* _collider;
	Mobility _mobility{ defaultMobility };
	Direction _direction{ defaultDirection };
	std::unordered_map<std::string, const char*> sfx;
public:
	friend class PlayerController;
	friend class ObjectController;

	const char* _SInteract{ SFX.item_pick };
public:
	Actor(std::string name = " ", CSimpleSprite* sprite = nullptr, Vector2D position = (0,0), Collision* collider = new Collision(32,32));
	Actor(Actor* actor);
	virtual ~Actor();

	const std::string& GetName() const;
	CSimpleSprite* GetSprite();
	Vector2D& GetPosition();
	Collision* GetCollider();
	const Mobility& GetMobility();
	const Direction& GetDirection();
	const std::string& GetTag();
	Actor* GetClosestActor(float ms = 0);

	void SetName(std::string name);
	void SetSprite(CSimpleSprite* sprite);
	void SetSprite(CSimpleSprite& sprite);
	void SetPosition(Vector2D position);
	void SetPosition(float x = 0, float y = 0);
	void SetCollider(Collision* collider);
	void SetDirection(Direction direction);
	void SetTag(std::string&& tag);
	void SetMobility(Mobility mobility);
};

#endif

