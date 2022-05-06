#pragma once
#ifndef ITEM_H_
#define ITEM_H_

#include "Actor.h"

class Item : public Actor
{
private:
protected:
public:
	Item(std::string name, CSimpleSprite* sprite, Vector2D& position, Collision* collider, Room* currentRoom);
	~Item();
};

#endif