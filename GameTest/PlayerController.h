#pragma once

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Controller.h"

class PlayerController : public Controller
{
private:
protected:
public:
	PlayerController(bool activated = true);
	~PlayerController();

	void MoveHorizontally(Character* actor) override;
	void MoveVertically(Character* actor) override;
};

#endif