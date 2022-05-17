#include "stdafx.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem(Usability usability, int ID) : usability{usability}, ID{ID}
{
}

bool InventoryItem::UseItem()
{
	return false;
}
