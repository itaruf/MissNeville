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
	std::cout << _description << std::endl;
	return true;
}
