#pragma once

#ifndef IINTERACTIVE_H_
#define IINTERACTIVE_H_

#include "Utilities.h"

#include <combaseapi.h>

// Set of functions to manage the interaction between the player and the target
interface IInteractive
{
public:
	Delegate onInteract;
public:
	virtual void Interact() = 0;
	virtual ~IInteractive() = default;
};

#endif