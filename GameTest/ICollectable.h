#pragma once

#include "InventoryItem.h"
#include <combaseapi.h>

class InventoryItem;
// Interface
interface ICollectable
{
public:
	// pure virtual function
	virtual InventoryItem* Collect() = 0;
	virtual ~ICollectable();
};
