#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../../../App/SimpleSound.h"

#include "../../Interfaces/IDialogue.h"
#include "../../Actors/Actor.h"
#include "../../Controllers/Controller.h"
#include "../../Systems/States/StateController.h"

class Controller;
class StateController;

// Class for entities which will be either playable or non-playable such as NPCs
class Character : public Actor
{
protected:
	float _HP;
	float _movementSpeed;
	Controller* _controller;
public:
	friend class PlayerController;
	friend class ObjectController;

	CSimpleSprite* _footStep;

	const char* _SDeath{SFX.ghost_death};
	const char* _SMove{ SFX.footstep2 };
public:
	Character(std::string name = " ", CSimpleSprite* sprite = nullptr, Vector2D position = (0,0), Collision* collider = nullptr, float HP = 0, float movementSpeed = 0, Controller* controller =  nullptr);
	virtual ~Character();

	const float& GetMovementSpeed() const;
	const float& GetHP() const;
	Controller* GetController() const;

	void SetHP(float value);
	void SetMovementSpeed(float value);

	bool IsMoving();

	virtual void MoveVertically();
	virtual void MoveHorizontally();
};  

#endif