#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Collectable.h"

#include <unordered_map>
#include <typeinfo>
#include <vector>

// Class to define an inventory with bags and slots
class Inventory
{
private:
	static constexpr int _nbBags{ 1 };
	static constexpr int _nbSlotBag{ 9 };
public:
	// Allow the Player class to access Inventory members
	friend class Player;
	std::unordered_map<int, std::pair<bool, std::vector<Collectable*>>> _bags;
public:
	Inventory() = default;
	Inventory(std::map<int, std::vector<Collectable*>>);
	~Inventory();

	bool AddItem(Collectable* item);
	bool RemoveItem(Collectable* item);
	bool IsBagExist(int ID);
	bool IsBagOpened(int ID);
	bool IsAnyBagAlreadyOpened();

	Collectable* GetItem(int ID, int slotNumber);

	inline static constexpr int GetNbSlotBag()
	{
		return _nbSlotBag;
	}

	inline static constexpr int GetNbBags()
	{
		return _nbBags;
	}
};

#endif