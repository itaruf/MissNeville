#pragma once

#include "IInteractive.h"
#include "InventoryItem.h"

class InventoryItem;
// Interface
class ICollectable
{
public:
	// pure virtual function
	virtual InventoryItem* Collect() = 0;
	virtual ~ICollectable();
};
