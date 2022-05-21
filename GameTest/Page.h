#pragma once
#ifndef PAGE_H_
#define PAGE_H_

#include "Collectable.h"
#include "IInteractive.h"
#include "InvPage.h"

class Page : public Collectable
{
private:
protected:
public:
	Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, InventoryItem* invItem, int ID = 0);
	~Page();

	InventoryItem* Collect() override;
};


#endif
