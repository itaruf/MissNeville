#pragma once

#include "InventoryItem.h"
#include <combaseapi.h>

class InventoryItem;

// Set of functions to manage the interaction between the player and the target
interface IInteractive
{
public:
	virtual void Interact() = 0;
	virtual ~IInteractive() = default;
};

