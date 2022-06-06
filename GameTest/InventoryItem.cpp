#include "stdafx.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem(Usability usability, int ID, std::string& description) : _usability{usability}, _ID{ID}, _description{std::move(description)}
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
