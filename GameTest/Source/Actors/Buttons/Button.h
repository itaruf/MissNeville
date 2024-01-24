#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../Interfaces/IInteractive.h"
#include "../../Utilities/Utilities.h"

// Class defining a button which has a specific interaction
class Button : public Actor, public IInteractive
{
protected:
	bool _activated{ true };
public:
	Delegate onActivated;
	Delegate onDeactivated;
public:
	Button(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, bool activated = true);
	~Button() = default;

	void Interact() override;

	bool isActivated();
};

#endif