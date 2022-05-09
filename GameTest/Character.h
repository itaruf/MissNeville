#pragma once
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Actor.h"
#include "app\app.h"
#include "EDirection.h"
#include "Candle.h"

class Candle;
class Character : public Actor
{
private:
protected:
	float HP;
	float movementSpeed;
	float grabXRange{ 10 };
	float grabYRange{ 100 };
	Vector2D grabRange{ position->x + grabXRange, position->y + grabYRange };
public:
	Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed);
	~Character() = default;

	const float& GetHP() const;
	void SetHP(float value);
	const float& GetMovementSpeed() const;
	void SetMovementSpeed(float value);
	bool isMoving();
	void MoveVertically();
	void MoveHorizontally();
	bool UseLighter(Candle* candle);
};
#endif
