#include "stdafx.h"
#include "Item.h"

Item::Item(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, std::shared_ptr<Room> currentRoom, Interactivity interactivity, int ID) : Actor(name, sprite, position, collider, currentRoom), interactivity{interactivity}, ID{ID}
{
}

Interactivity Item::GetInteractivity()
{
	return interactivity;
}
