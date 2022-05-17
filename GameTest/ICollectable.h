#pragma once

#include "ICollectable.h"

class InventoryItem;
// Interface
class ICollectable
{
public:
	// pure virtual function
	virtual InventoryItem* Collect() = 0;
	virtual ~ICollectable() = default;
};

