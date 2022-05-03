#pragma once
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Actor.h"
#include "app\app.h"
#include "EDirection.h"

class Character : public Actor
{
private:
protected:
	float HP;
	float movementSpeed;
public:
	Character(std::string name, CSimpleSprite*& sprite, Vector2D& position, Collision*& collider, Room* currentRoom, float HP, float movementSpeed);
	~Character() = default;

	float& GetHP();
	void SetHP(float value);
	float& GetMovementSpeed();
	void SetMovementSpeed(float value);
	bool isMoving();
	void MoveVertically();
	void MoveHorizontally();
};
#endif
