#include "stdafx.h"
#include "Collectable.h"

Collectable::Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, InventoryItem* invItem, int ID) : Actor(name, sprite, position, collider), ID{ ID }, invItem{ invItem }
{
}

Collectable::~Collectable()
{
	printf("ITEM DESTRUCTOR CALLED\n");

	// Freeing all the memory allocated on the heap
	/*delete invItem;
	invItem = nullptr;*/
}