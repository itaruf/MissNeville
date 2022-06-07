#include "stdafx.h"
#include "Page.h"

Page::Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, int ID, std::string description) : Collectable(name, sprite, position, collider, ID, description)
{
}

Page::~Page()
{
	printf("PAGE DESTRUCTOR CALLED\n");
}

bool Page::UseItem()
{
	return false;
	std::cout << _description << std::endl;
}

//// return the associated item
//InventoryItem* Page::Collect()
//{
//	/*std::string description{ "page" };*/
//	/*return new InvPage(InventoryItem::Usability::Usable, 0, description);*/
//
//	return _invItem;
//}
