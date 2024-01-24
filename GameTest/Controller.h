#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Character;

class Controller
{
public:
	bool _activated;
public:
	Controller(bool activated = true);
	virtual ~Controller() = default;

	virtual void MoveHorizontally(Character* actor) = 0;
	virtual void MoveVertically(Character* actor) = 0;

	void SetActivation(bool value);
};

#endif // !CONTROLLER_H