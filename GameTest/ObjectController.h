#pragma once
#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include "Controller.h"

class ObjectController : public Controller
{
private:
protected:
public:
	ObjectController();
	~ObjectController();

	void MoveHorizontally(Character* actor) override;
	void MoveVertically(Character* actor) override;
};

#endif