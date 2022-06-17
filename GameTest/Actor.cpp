#include "../stdafx.h"
#include "Actor.h"

Actor::Actor(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : _name{ std::move(name) }, _sprite(std::move(sprite)), _position{ position }, _collider{ std::move(collider)}
{

	// Immediately Set the position of the actor 
	SetPosition(position);
}

Actor::Actor(Actor* actor) : _name(actor->_name), _sprite(actor->_sprite), _position(actor->_position), _collider(actor->_collider), _mobility(actor->_mobility), _direction(actor->_direction)
{
}

Actor::~Actor()
{	std::cout << "ACTOR DESTRUCTOR CALLED" << std::endl;

	// Freeing all the memory allocated on the heap

	if (_sprite)
		delete _sprite;

	if (_position)
		delete _position;

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

	_sprite = sprite;
	// Immediately Set the position of the sprite and thus, of the actor

	if (!_position)
		return;

	_sprite->SetPosition(_position->_x, _position->_y);
}

// Set the sprite of the actor
void Actor::SetSprite(CSimpleSprite& sprite)
{
	*(_sprite) = sprite;
	// Immediately Set the position of the sprite and thus, of the actor
	_sprite->SetPosition(_position->_x, _position->_y);
}

// Get the current position of the actor
Vector2D* Actor::GetPosition()
{
	if (!_sprite)
		return nullptr;

	if (!_position)
		return nullptr;

	// The sprite of the actor manages its position
	_sprite->GetPosition(_position->_x, _position->_y);
	return _position;
}

// Set the position of the actor
void Actor::SetPosition(Vector2D* position)
{
	if (!_sprite)
		return;

	if (!position)
		return;

	_sprite->SetPosition(position->_x, position->_y);
	_position->_x = position->_x;
	_position->_y = position->_y;
}

// Set the position of the actor
void Actor::SetPosition(float x, float y)
{
	if (!_sprite)
		return;

	_sprite->SetPosition(x, y);
	_position->_x = x;
	_position->_y = y;
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
