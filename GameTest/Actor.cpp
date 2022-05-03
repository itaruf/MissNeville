#include "stdafx.h"
#include "Actor.h"

Actor::Actor(std::string name, CSimpleSprite*& sprite, Vector2D& position, Collision*& collider, Room* currentRoom) : name{ std::move(name) }, sprite(sprite), position{ position }, collider{ std::move(collider) }, currentRoom{ std::move(currentRoom)}
{
	SetPosition(position);
}

const std::string& Actor::GetName() const
{
	return name;
}

void Actor::SetName(std::string name)
{
	this->name = name;
}

CSimpleSprite* Actor::GetSprite()
{
	return sprite;
}

void Actor::SetSprite(CSimpleSprite*& sprite)
{
	this->sprite = sprite;
	this->sprite->SetPosition(position.x, position.y);
}

void Actor::SetSprite(CSimpleSprite& sprite)
{
	*(this->sprite) = sprite;
	this->sprite->SetPosition(position.x, position.y);
}


const Vector2D& Actor::GetPosition()
{
	sprite->GetPosition(position.x, position.y);
	return position;
}

void Actor::SetPosition(Vector2D& position)
{
	sprite->SetPosition(position.x, position.y);
	this->position = GetPosition();
}

void Actor::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	position.x = x;
	position.y = y;
}

Collision* Actor::GetCollider()
{
	return collider;
}

void Actor::SetCollider(Collision* collider)
{
	this->collider = collider;
}

Room* Actor::GetCurrentRoom()
{
	return currentRoom;
}
