#pragma once
#ifndef ITEM_H_
#define ITEM_H_

#include "Actor.h"
#include "Interactivity.h"
#include "ICollectable.h"
#include "InventoryItem.h"

class Collectable : public Actor, public ICollectable
{
private:
protected:
	InventoryItem* invItem;
public:
	int ID;
	Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, InventoryItem* invItem, int ID = 0);
	~Collectable();
};

#endif