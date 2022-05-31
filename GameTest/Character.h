#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Actor.h"

// Class for entities which will be either playable or non-playable such as NPCs
class Character : public Actor
{
private:
protected:
	float HP;
	float movementSpeed;
public:
	Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed);
	~Character();

	const float& GetMovementSpeed() const;
	const float& GetHP() const;
	bool IsMoving();

	void SetHP(float value);
	void SetMovementSpeed(float value);
};

#endif