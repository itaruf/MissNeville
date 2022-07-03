#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

class StateController;
#include "StateController.h"
#include "Actor.h"
class Controller;
#include "Controller.h"

#include "IDialogue.h"
#include "App/SimpleSound.h"

// Class for entities which will be either playable or non-playable such as NPCs
class Character : public Actor
{
private:
protected:
	float _HP;
	float _movementSpeed;
	Controller* _controller;
public:
	friend class PlayerController;
	friend class ObjectController;

	CSimpleSprite* _footStep;

	/*static CSimpleSound& _SFXDeath;
	static CSimpleSound& _SFXInteract;*/

	const char* _SDeath{SFX.ghost_death};
	const char* _SMove{ SFX.footstep2 };

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