#pragma once

#include "IInteractive.h"
#include "InventoryItem.h"

class InventoryItem;
// Interface
class IInteractive
{
public:
	// pure virtual function
	virtual void Interact() = 0;
	virtual ~IInteractive();
};

