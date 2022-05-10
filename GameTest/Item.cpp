#include "stdafx.h"
#include "Item.h"

Item::Item(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, Interactivity Interactivity) : Actor(name, sprite, position, collider, currentRoom)
{
}

Interactivity Item::GetInteractivity()
{
	return interactivity;
}
