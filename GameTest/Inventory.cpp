#include "stdafx.h"
#include "Inventory.h"

void Inventory::AddItem(Item* item)
{
	items.emplace_back(item);
}
