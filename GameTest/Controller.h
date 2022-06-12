#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Character;

class Controller
{
private:
protected:
public:
	Controller();
	virtual ~Controller();

	virtual void MoveHorizontally(Character* actor) = 0;
	virtual void MoveVertically(Character* actor) = 0;
};


#endif // !CONTROLLER_H
