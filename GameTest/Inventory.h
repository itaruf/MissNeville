#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Collectable.h"
#include "Page.h"
#include <vector>
#include "InventoryItem.h"
#include <map>
#include <stdexcept>      // std::length_error

class Inventory
{
private:
protected:
public:
	std::map<int, std::pair<bool, std::vector<InventoryItem*>>> bags;
	Inventory();
	Inventory(std::map<int, std::vector<InventoryItem*>>);
	~Inventory();

	bool AddItem(InventoryItem* item);
	bool RemoveItem(InventoryItem* item);
	bool IsBagExist(int ID);
	InventoryItem* GetItem(int ID, int slotNumber);
};

#endif
