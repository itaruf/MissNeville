#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Collectable.h"
#include "Page.h"
#include <vector>
#include "InventoryItem.h"
#include <unordered_map>

// Class to define an inventory with bags and slots
class Inventory
{
private:
	static constexpr int _nbBags{ 1 };
	static constexpr int _nbSlotBag{ 9 };
protected:
public:
	// Allow the Player class to access Inventory members
	friend class Player;
	std::unordered_map<int, std::pair<bool, std::vector<InventoryItem*>>> _bags;
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
