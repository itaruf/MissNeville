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
	static constexpr int nbBags{ 4 };
	static constexpr int nbSlotBag{ 6 };
protected:
public:
	friend class Character;
	std::map<int, std::pair<bool, std::vector<InventoryItem*>>> bags;
	Inventory();
	Inventory(std::map<int, std::vector<InventoryItem*>>);
	~Inventory();

	bool AddItem(InventoryItem* item);
	bool RemoveItem(InventoryItem* item);
	bool IsBagExist(int ID);
	bool IsBagOpened(int ID);
	bool IsAnyBagAlreadyOpened();
	InventoryItem* GetItem(int ID, int slotNumber);
};

#endif
