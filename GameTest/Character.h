#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

class GameState;
#include "GameState.h"
#include "Actor.h"
class Controller;
#include "Controller.h"

// Class for entities which will be either playable or non-playable such as NPCs
class Character : public Actor
{
private:
protected:
	float _HP;
	float _movementSpeed;
	Controller* _controller;
public:
	Character(std::string name = " ", CSimpleSprite* sprite = nullptr, Vector2D* position = nullptr, Collision* collider = nullptr, float HP = 0, float movementSpeed = 0, Controller* controller =  nullptr);
	virtual ~Character();

	const float& GetMovementSpeed() const;
	const float& GetHP() const;
	Controller* GetController() const;
	bool IsMoving();

	void SetHP(float value);
	void SetMovementSpeed(float value);

	virtual void MoveVertically();
	virtual void MoveHorizontally();
};

#endif