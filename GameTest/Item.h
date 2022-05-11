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
	Item(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, Interactivity interactivity);
	~Item() = default;
	Interactivity GetInteractivity();
};

#endif