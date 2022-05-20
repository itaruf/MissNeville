#include "stdafx.h"
#include "Page.h"

Page::Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, Interactivity interactivity) : Item(name, sprite, position, collider, currentRoom, interactivity)
{
}

Page::~Page()
{
	printf("PAGE DESTRUCTOR CALLED\n");
}

InventoryItem* Page::Collect()
{
	std::string description{ "page" };
	return new InvPage(InventoryItem::Usability::Usable, 0, description);
}
