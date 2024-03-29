#include "../stdafx.h"
#include "Actor.h"

Actor::Actor(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider) : _name{ std::move(name) }, _sprite(std::move(sprite)), _position{ position }, _collider{ std::move(collider) }
{
	// Immediately Set the position of the actor 

	if (!StateController::_currentScene)
		return;

	if (StateController::_currentScene->initialized)
	{
		SetPosition(position);
		StateController::_currentScene->AddActor(this);
	}
}

Actor::Actor(Actor* actor) : _name(actor->_name), _sprite(actor->_sprite), _position(actor->_position), _collider(actor->_collider), _mobility(actor->_mobility), _direction(actor->_direction)
{
}

Actor::~Actor()
{
	if (_sprite)
		delete _sprite;

	if (_collider)
		delete _collider;
}

// Get the current name of the actor
const std::string& Actor::GetName() const
{
	return _name;
}

// Set the name of the actor
void Actor::SetName(std::string name)
{
	_name = name;
}

// Get the sprite of the actor
CSimpleSprite* Actor::GetSprite()
{
	return _sprite;
}

// Set the sprite of the actor
void Actor::SetSprite(CSimpleSprite* sprite)
{
	if (!sprite)
		return;

	delete _sprite;

	_sprite = sprite;
	// Immediately Set the position of the sprite and thus, of the actor

	_sprite->SetPosition(_position.x, _position.y);
}

// Set the sprite of the actor
void Actor::SetSprite(CSimpleSprite& sprite)
{
	*(_sprite) = sprite;
	// Immediately Set the position of the sprite and thus, of the actor
	_sprite->SetPosition(_position.x, _position.y);
}

// Get the current position of the actor
Vector2D& Actor::GetPosition()
{
	if (!_sprite)
		_position;

	// The sprite of the actor manages its position
	_sprite->GetPosition(_position.x, _position.y);
	return _position;
}

// Set the position of the actor
void Actor::SetPosition(Vector2D position)
{
	if (!_sprite)
		return;

	_sprite->SetPosition(position.x, position.y);
}

// Set the position of the actor
void Actor::SetPosition(float x, float y)
{
	if (!_sprite)
		return;

	_sprite->SetPosition(x, y);
}

// Return the collider of the actor
Collision* Actor::GetCollider()
{
	return _collider;
}

// Set the collider of the actor
void Actor::SetCollider(Collision* collider)
{
	_collider = collider;
}

void Actor::SetDirection(Direction direction)
{
	_direction = direction;
}

void Actor::SetTag(std::string&& tag)
{
	_tag = tag;
}

void Actor::SetMobility(Mobility mobility)
{
	_mobility = mobility;
}

// Get the mobility of the actor (STATIC, MOVABLE)
const Mobility& Actor::GetMobility()
{
	return _mobility;
}

// Get the current direction of the actor (STILL, FW, BW, LEFT, RIGHT)
const Direction& Actor::GetDirection()
{
	return _direction;
}

const std::string& Actor::GetTag()
{
	return _tag;
}

Actor* Actor::GetClosestActor(float ms)
{
	auto actors{ StateController::_currentScene->GetActors() };

	if (actors.size() <= 0)
		return nullptr;

	std::vector<Actor*> interactiveActors{};

	// Select all Collectable or Interactive actors
	for (auto& actor : actors)
		if (dynamic_cast<ICollectable*>(actor) || dynamic_cast<IInteractive*>(actor) || actor->GetMobility() == Mobility::MOVABLE)
			interactiveActors.emplace_back(actor);

	if (interactiveActors.size() <= 0)
		return nullptr;

	if (GetDirection() == Direction::LEFT || GetDirection() == Direction::DOWN)
		ms = -ms;

	float x{ GetPosition().x };
	float y{ GetPosition().y };

	if (GetDirection() == Direction::RIGHT || GetDirection() == Direction::LEFT)
		x = GetPosition().x + ms;
	else
		y = GetPosition().y + ms;

	/*SORT : FROM CLOSEST ACTOR TO FARTHEST*/
	std::sort(std::begin(interactiveActors), std::end(interactiveActors), [this, ms](Actor* const& l, Actor* const& r)
		{
			return
				std::abs(GetPosition().x + ms - l->GetPosition().x + ms) + std::abs(GetPosition().y + ms - l->GetPosition().y + ms)
				<
				std::abs(GetPosition().x + ms - r->GetPosition().x + ms) + std::abs(GetPosition().y + ms - r->GetPosition().y + ms);
		});

	if (!GetCollider()->isColliding(this, interactiveActors[0], x, y))
		return nullptr;

	return (interactiveActors[0]);
}