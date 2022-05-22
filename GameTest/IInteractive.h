#pragma once

#include "InventoryItem.h"
#include <combaseapi.h>

class InventoryItem;
// Interface
interface IInteractive
{
public:
	// pure virtual function
	virtual void Interact() = 0;
	virtual ~IInteractive();
};

