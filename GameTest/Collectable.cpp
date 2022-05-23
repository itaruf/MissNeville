#include "stdafx.h"
#include "Collectable.h"

Collectable::Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* currentScene, InventoryItem* invItem, int ID) : Actor(name, sprite, position, collider, currentScene), ID{ ID }, invItem{ invItem }
{
}

Collectable::~Collectable()
{
	printf("ITEM DESTRUCTOR CALLED\n");
}