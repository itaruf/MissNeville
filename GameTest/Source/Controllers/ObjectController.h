#pragma once
#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "Controller.h"
#include "../Utilities/Utilities.h"

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