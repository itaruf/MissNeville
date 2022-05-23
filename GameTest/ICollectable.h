#pragma once

#include "InventoryItem.h"
#include <combaseapi.h>

class InventoryItem;
// Set of functions to manage the interaction between the player and the target (collectable)
interface ICollectable
{
public:
	virtual InventoryItem* Collect() = 0;
	virtual ~ICollectable() = default;
};
