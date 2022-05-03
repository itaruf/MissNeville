#include "stdafx.h"
#include "Actor.h"

Actor::Actor(std::string name, CSimpleSprite*& sprite, Vector2D& position, Collision*& collider, Room* currentRoom) : name{ std::move(name) }, sprite{ std::move(sprite) }, position{ position }, collider{ std::move(collider) }, currentRoom{ std::move(currentRoom)}
{
	SetPosition(position);
}

std::string& Actor::GetName()
{
	return name;
}

CSimpleSprite*& Actor::GetSprite()
{
	return sprite;
}

void Actor::SetSprite(CSimpleSprite* sprite)
{
	sprite->SetPosition(position.x, position.y);
	this->sprite = sprite;
}

Vector2D& Actor::GetPosition()
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

Collision*& Actor::GetCollider()
{
	return collider;
}

Room*& Actor::GetCurrentRoom()
{
	return currentRoom;
}
