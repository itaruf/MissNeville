#include "stdafx.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem(Usability usability, int ID) : usability{usability}, ID{ID}
{
}

InventoryItem::~InventoryItem()
{
	printf("INVENTORYITEM DESTRUCTOR CALLED\n");
}

bool InventoryItem::UseItem()
{
	return false;
}
