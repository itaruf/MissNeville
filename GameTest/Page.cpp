#include "stdafx.h"
#include "Page.h"

Page::Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, InventoryItem* invItem, int ID) : Collectable(name, sprite, position, collider, invItem, ID)
{
}

Page::~Page()
{
	printf("PAGE DESTRUCTOR CALLED\n");
}

// return the associated item
InventoryItem* Page::Collect()
{
	/*std::string description{ "page" };*/
	/*return new InvPage(InventoryItem::Usability::Usable, 0, description);*/

	return _invItem;
}
