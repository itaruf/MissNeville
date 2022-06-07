#pragma once

#include <combaseapi.h>

// Set of functions to manage the interaction between the player and the target (collectable)
interface ICollectable
{
public:
	// Each item will have its own treatment
	virtual bool UseItem() = 0;
	virtual ~ICollectable() = default;
};
