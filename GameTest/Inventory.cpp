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
	for (auto key : items)
		for (auto item : key.second)
			if (item)
				delete item;
}

InventoryItem* Inventory::GetItem(int ID)
{
	return items[ID][0];
}


bool Inventory::RemoveItem(InventoryItem* item)
{
	return false;
}

bool Inventory::RemoveItem(int ID)
{
	return false;
}

bool Inventory::AddItem(InventoryItem* item)
{
	if (!item)
		return false;

	// Check if key exists
	if (items.find(item->ID) != items.end())
	{
		items[item->ID].emplace_back(item);
		return true;
	}

	// Create a key if it doesnt exist
	else 
	{
		items.insert(std::make_pair(item->ID, std::vector<InventoryItem*>({ item })));
		return true;
	}
}

