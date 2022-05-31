#include "stdafx.h"
#include "Actor.h"

Actor::Actor(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : name{ std::move(name) }, sprite(std::move(sprite)), position{ position }, collider{ std::move(collider)}
{

	// Immediately Set the position of the actor 
	SetPosition(position);
}

Actor::Actor(Actor* actor) : name(actor->name), sprite(actor->sprite), position(actor->position), collider(actor->collider), mobility(actor->mobility), direction(actor->direction)
{
}

Actor::~Actor()
{	std::cout << "ACTOR DESTRUCTOR CALLED" << std::endl;

	// Freeing all the memory allocated on the heap

	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}

	if (position)
	{
		delete position;
		position = nullptr;
	}

	if (collider)
	{
		delete collider;
		collider = nullptr;
	}
}

// Get the current name of the actor
const std::string& Actor::GetName() const
{
	return name;
}

// Set the name of the actor
void Actor::SetName(std::string name)
{
	this->name = name;
}

// Get the sprite of the actor
CSimpleSprite* Actor::GetSprite()
{
	return sprite;
}

// Set the sprite of the actor
void Actor::SetSprite(CSimpleSprite* sprite)
{
	this->sprite = sprite;
	// Immediately Set the position of the sprite and thus, of the actor
	this->sprite->SetPosition(position->x, position->y);
}

// Set the sprite of the actor
void Actor::SetSprite(CSimpleSprite& sprite)
{
	*(this->sprite) = sprite;
	// Immediately Set the position of the sprite and thus, of the actor
	this->sprite->SetPosition(position->x, position->y);
}

// Get the current position of the actor
Vector2D* Actor::GetPosition()
{
	// The sprite of the actor manages its position
	sprite->GetPosition(position->x, position->y);
	return position;
}

// Set the position of the actor
void Actor::SetPosition(Vector2D* position)
{
	sprite->SetPosition(position->x, position->y);
	this->position = GetPosition();
}

// Set the position of the actor
void Actor::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	position->x = x;
	position->y = y;
}

// Return the collider of the actor
Collision* Actor::GetCollider()
{
	return collider;
}

// Set the collider of the actor
void Actor::SetCollider(Collision* collider)
{
	this->collider = collider;
}

// Get the mobility of the actor (STATIC, MOVABLE)
const Mobility& Actor::GetMobility()
{
	return mobility;
}

// Get the current direction of the actor (STILL, FW, BW, LEFT, RIGHT)
const Direction& Actor::GetDirection()
{
	return direction;
}