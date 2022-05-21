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

	for (auto& key : bags)
		for (auto& item : key.second.second)
				delete item;
}

InventoryItem* Inventory::GetItem(int ID, int slotNumber)
{
	if (!IsBagExist(ID))
		return nullptr;

	if (bags[ID].second.size() - 1 >= slotNumber)
		return bags[ID].second[slotNumber];
	else 
		return nullptr;
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

bool Inventory::AddItem(InventoryItem* item)
{
	if (!item)
		return false;

	// Check if key exists
	if (IsBagExist(item->ID))
	{
		bags[item->ID].second.emplace_back(item);
		item = nullptr;
		return true;
	}

	// Create a key if it doesnt exist
	else 
	{
		bags.insert(std::make_pair(item->ID, std::make_pair(false, std::vector<InventoryItem*>({ item }))));
		item = nullptr;
		return true;
	}
}

