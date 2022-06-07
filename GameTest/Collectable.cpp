#include "stdafx.h"
#include "Collectable.h"

Collectable::Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, int ID, std::string description) : Actor(name, sprite, position, collider), _ID{ ID }, _description{ std::move(description) }
{
}

Collectable::~Collectable()
{
	printf("ITEM DESTRUCTOR CALLED\n");
}