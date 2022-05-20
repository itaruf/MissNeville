#pragma once
#ifndef PAGE_H_
#define PAGE_H_

#include "Item.h"
#include "ICollectable.h"
#include "InvPage.h"

class Page : public Item, public ICollectable
{
private:
protected:
public:
	Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, Interactivity interactivity);
	~Page();

	InventoryItem* Collect() override;
};


#endif
