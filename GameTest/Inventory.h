#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Collectable.h"
#include "Page.h"
#include <vector>
#include "InventoryItem.h"
#include <map>

class Inventory
{
private:
protected:
public:
	std::map<int, std::vector<InventoryItem*>> items;
	Inventory();
	Inventory(std::map<int, std::vector<InventoryItem*>>);
	~Inventory();

	bool AddItem(InventoryItem* item);
	bool RemoveItem(InventoryItem* item);
	bool RemoveItem(int ID);

	InventoryItem* GetItem(int ID);
};

#endif
