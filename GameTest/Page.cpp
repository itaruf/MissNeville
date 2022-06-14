#include "../stdafx.h"
#include "Page.h"

Page::Page(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, int ID, std::string description) : Collectable(name, sprite, position, collider, ID, description)
{
	_SCollected = SFX.page_read;
	_SUsed = SFX.page_read;
}

Page::~Page()
{
}

bool Page::UseItem()
{
	CSimpleSound::GetInstance().PlaySoundW(_SUsed, 0);
	std::cout << _description << std::endl;
	return true;
}
