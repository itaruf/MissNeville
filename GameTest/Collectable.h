#pragma once
#ifndef ITEM_H_
#define ITEM_H_

#include "Actor.h"
#include "Interactivity.h"
#include "ICollectable.h"
#include "InventoryItem.h"

class Collectable : public Actor
{
private:
protected:
	InventoryItem* invItem;
public:
	int ID;
	Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, InventoryItem* invItem, int ID = 0);
	~Collectable();
	virtual InventoryItem* Collect() = 0;
};

#endif