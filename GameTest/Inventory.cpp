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

	for (auto& bag : bags)
		for (auto& item : bag.second.second)
		{
			delete item;
			item = nullptr;
		}
}

InventoryItem* Inventory::GetItem(int ID, int slotNumber)
{
	if (!IsBagExist(ID))
		return nullptr;

	return bags[ID].second[slotNumber];
}


bool Inventory::RemoveItem(InventoryItem* item)
{
	if (IsBagExist(item->ID))
	{
		auto it = std::find(bags[item->ID].second.begin(), bags[item->ID].second.end(), item);
		if (it != bags[item->ID].second.end())
		{
			bags[item->ID].second.erase(it);
			delete item;
			item = nullptr;
			return true;
		}
	}
	item = nullptr;
	return false;
}

bool Inventory::IsBagExist(int ID)
{
	if (bags.find(ID) != bags.end())
		return true;
	return false;
}

bool Inventory::IsBagOpened(int ID)
{
	if (!IsBagExist(ID))
		return false;

	if (bags[ID].first)
		return true;

	return false;
}

bool Inventory::IsAnyBagAlreadyOpened()
{
	for (auto i = 0; i < nbBags; ++i)
	{
		if (IsBagOpened(i))
			return true;
	}

	return false;
}

bool Inventory::AddItem(InventoryItem* item)
{
	if (!item)
		return false;

	// Check if key exists
	if (IsBagExist(item->ID))
	{

		for (auto& bagSlot : bags[item->ID].second)
		{
			if (!bagSlot)
			{
				std::cout << "item ID : " << item->ID << " added to the inventory" << std::endl;
				bagSlot = item;
				item = nullptr;
				return true;
			}
		}
	}

	std::cout << "item ID : " << item->ID << " couldn't be added to the inventory" << std::endl;
	item = nullptr;
	return false;
}


