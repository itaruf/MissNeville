#pragma once
#ifndef ITEM_H_
#define ITEM_H_

#include "Actor.h"
#include "Interactivity.h"

class Item : public Actor
{
private:
protected:
	Interactivity interactivity;
public:
	int ID;
	Item(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, std::shared_ptr<Room> currentRoom, Interactivity interactivity, int ID = 0);
	~Item() = default;
	Interactivity GetInteractivity();
};

#endif