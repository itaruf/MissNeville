#pragma once
#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include "Actor.h"
#include "ICollectable.h"
#include "InventoryItem.h"

// Actor which can be collected by the player and itemized
class Collectable : public Actor
{
private:
protected:
	InventoryItem* invItem;
public:
	int ID;
	Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* currentScene, InventoryItem* invItem, int ID = 0);
	~Collectable();

	// Each Collectable will have its own treatment
	virtual InventoryItem* Collect() = 0;
};

#endif