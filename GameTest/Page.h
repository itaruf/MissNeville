#pragma once
#ifndef PAGE_H_
#define PAGE_H_

#include "Collectable.h"

// Class which represents a page which has a specific interaction
class Page : public Collectable
{
public:
	Page(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, int ID = 0, std::string description = " ");
	~Page() = default;

	void UseItem() override;
};

#endif