#pragma once

#include "Utilities.h"
#include <combaseapi.h>

// Set of functions to manage the interaction between the player and the target
interface IInteractive
{
public:
	Delegate _onInteract;
	virtual void Interact() = 0;
	virtual ~IInteractive() = default;
};

