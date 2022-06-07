#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::Inventory(std::map<int, std::vector<Collectable*>>)
{
}

Inventory::~Inventory()
{
	printf("INVENTORY DESTRUCTOR CALLED\n");

	//Freeing the memory allocated on the heap
	for (auto& bag : _bags)
		for (auto& item : bag.second.second)
		{
			if (item)
				delete item;
		}
}

// Return the stored item at a slot of a bag
Collectable* Inventory::GetItem(int ID, int slotNumber)
{
	return _bags[ID].second[slotNumber];
}


// Remove a stored item (when we know which item it is)
bool Inventory::RemoveItem(Collectable* item)
{
	// Check if the corresponding bag exists
	if (!IsBagExist(item->_ID))
		return false;

		// Go through the bag slots to find the item
	auto it = std::find(_bags[item->_ID].second.begin(), _bags[item->_ID].second.end(), item);
	if (it != _bags[item->_ID].second.end())
	{
		// delete the item when found
		_bags[item->_ID].second.erase(it);
		delete item;
		return true;
	}
	// item not found
	return false;
}

// Check if a bag exists (decided with ID)
bool Inventory::IsBagExist(int ID)
{
	return (_bags.find(ID) != _bags.end());
}

// Check if a bag is opened (decided with ID)
bool Inventory::IsBagOpened(int ID)
{
	if (!IsBagExist(ID))
		return false;

	return _bags[ID].first;
}

// Check if any bag is opened
bool Inventory::IsAnyBagAlreadyOpened()
{
	for (auto i = 0; i < _nbBags; ++i)
	{
		// return at the first opened bag found
		if (IsBagOpened(i))
			return true;
	}
	return false;
}

// Add an item at the corresponding bag (decided with ID)
bool Inventory::AddItem(Collectable* item)
{
	if (!item)
		return false;

	// Check if bag exists
	if (!IsBagExist(item->_ID))
		return false;

	// Looking for an empty slot
	for (auto& slot : _bags[item->_ID].second)
	{
		if (!slot)
		{
			// Add the item at first empty slot found
			std::cout << "item ID : " << item->_ID << " added to the inventory" << std::endl;
			slot = item;
			return true;
		}

	}

	// No free slot found
	std::cout << "item ID : " << item->_ID << " couldn't be added to the inventory" << std::endl;
	return false;
}


