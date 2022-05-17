#include "stdafx.h"
#include "Page.h"

Page::Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, std::shared_ptr<Room> currentRoom, Interactivity interactivity) : Item(name, sprite, position, collider, currentRoom, interactivity)
{
}

Page::~Page()
{
}

InventoryItem* Page::Collect()
{
	return new InvPage(InventoryItem::Usability::Usable, 0);
}
