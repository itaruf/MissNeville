#pragma once
#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "Controller.h"
#include "Utilities.h"

class ObjectController : public Controller
{
private:
protected:
public:
	Delegate _onChangeDirection;
	ObjectController(bool activated = true);
	~ObjectController();

	void MoveHorizontally(Character* actor) override;
	void MoveVertically(Character* actor) override;
};

#endif