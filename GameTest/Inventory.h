#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Item.h"
#include "Page.h"
#include <vector>

class Inventory
{
private:
	std::vector<Item*> items;
	std::vector<Page*> pages;
protected:
public:

	void AddItem(Item* item);
	Item* GetItem();
};

#endif
