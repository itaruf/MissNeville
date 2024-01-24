#pragma once
#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "../Utilities/Utilities.h"

#include "Controller.h"

class ObjectController : public Controller
{
public:
	Delegate onChangeDirection;
public:
	ObjectController(bool activated = true);
	~ObjectController() = default;

	void MoveHorizontally(Character* actor) override;
	void MoveVertically(Character* actor) override;
};

#endif