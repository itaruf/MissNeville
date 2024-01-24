#include "../stdafx.h"
#include "Inventory.h"

Inventory::Inventory(std::map<int, std::vector<Collectable*>>)
{
}

Inventory::~Inventory()
{
	for (auto& bag : _bags)
		for (auto& item : bag.second.second)
			if (item)
				delete item;
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
	if (!IsBagExist(0))
		return false;

		// Go through the bag slots to find the item
	auto it = std::find(_bags[0].second.begin(), _bags[0].second.end(), item);

	// item not found
	if (it == _bags[0].second.end())
		return false;
	
	*it = nullptr;
	std::cout << item->GetName() << " removed" << std::endl;
	delete item;
	return true;
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
	for (auto i = 0; i < GetNbBags(); ++i)
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
	if (!IsBagExist(0))
		return false;

	// Looking for an empty slot
	for (auto& slot : _bags[0].second)
	{
		if (slot)
			continue;
		// Add the item at first empty slot found
		std::cout << "item ID : " << 0 << " added to the inventory" << std::endl;
		slot = item;
		return true;
	}

	// No free slot found
	std::cout << "item ID : " << 0 << " couldn't be added to the inventory" << std::endl;
	return false;
}