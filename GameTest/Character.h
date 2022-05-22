#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Actor.h"

class Character : public Actor
{
private:
protected:
	float HP;
	float movementSpeed;
public:
	Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed);
	~Character();

	const float& GetMovementSpeed() const;
	const float& GetHP() const;
	bool isMoving();

	void SetHP(float value);
	void SetMovementSpeed(float value);
};

#endif