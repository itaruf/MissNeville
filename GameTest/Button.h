#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "IInteractive.h"
#include "Utilities.h"

// Class defining a button which has a specific interaction
class Button : public Actor, public IInteractive
{
private:
protected:
	bool _activated{ true };
public:
	Delegate _onActivated;
	Delegate _onDeactivated;

	Button(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated = true);
	~Button();

	bool isActivated();
	void Interact() override;
};

#endif