#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::Inventory(std::map<int, std::vector<InventoryItem*>>)
{
}

Inventory::~Inventory()
{
	printf("INVENTORY DESTRUCTOR CALLED\n");

	//Freeing the memory allocated on the heap
	for (auto& bag : bags)
		for (auto& item : bag.second.second)
		{
			delete item;
			item = nullptr;
		}
}

// Return the stored item at a slot of a bag
InventoryItem* Inventory::GetItem(int ID, int slotNumber)
{
	return bags[ID].second[slotNumber];
}


// Remove a stored item (when we know which item it is)
bool Inventory::RemoveItem(InventoryItem* item)
{
	// Check if the corresponding bag exists
	if (IsBagExist(item->ID))
	{
		// Go through the bag slots to find the item
		auto it = std::find(bags[item->ID].second.begin(), bags[item->ID].second.end(), item);
		if (it != bags[item->ID].second.end())
		{
			// delete the item when found
			bags[item->ID].second.erase(it);
			delete item;
			item = nullptr;
			return true;
		}
	}
	// item not found
	item = nullptr;
	return false;
}

// Check if a bag exists (decided with ID)
bool Inventory::IsBagExist(int ID)
{
	return (bags.find(ID) != bags.end());
}

// Check if a bag is opened (decided with ID)
bool Inventory::IsBagOpened(int ID)
{
	if (!IsBagExist(ID))
		return false;

	return bags[ID].first;
}

// Check if any bag is opened
bool Inventory::IsAnyBagAlreadyOpened()
{
	for (auto i = 0; i < nbBags; ++i)
	{
		// return at the first opened bag found
		if (IsBagOpened(i))
			return true;
	}
	return false;
}

// Add an item at the corresponding bag (decided with ID)
bool Inventory::AddItem(InventoryItem* item)
{
	if (!item)
		return false;

	// Check if bag exists
	if (IsBagExist(item->ID))
	{
		// Looking for an empty slot
		for (auto& bagSlot : bags[item->ID].second)
		{
			if (!bagSlot)
			{
				// Add the item at first empty slot found
				std::cout << "item ID : " << item->ID << " added to the inventory" << std::endl;
				bagSlot = item;
				item = nullptr;
				return true;
			}
		}
	}

	// No free slot found
	std::cout << "item ID : " << item->ID << " couldn't be added to the inventory" << std::endl;
	item = nullptr;
	return false;
}


