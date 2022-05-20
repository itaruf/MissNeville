#include "stdafx.h"
#include "Item.h"

Item::Item(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, Interactivity interactivity, int ID) : Actor(name, sprite, position, collider, currentRoom), interactivity{interactivity}, ID{ID}
{
}

Item::~Item()
{
	printf("ITEM DESTRUCTOR CALLED\n");
}

Interactivity Item::GetInteractivity()
{
	return interactivity;
}
