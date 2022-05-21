#pragma once
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Actor.h"
#include "app\app.h"
#include "EDirection.h"
#include "Candle.h"
#include "Inventory.h"
#include "ICollectable.h"

class Candle;
class Character : public Actor
{
private:
protected:
	float HP;
	float movementSpeed;
	float grabRange{ 500 };
public:
	Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed, Inventory* inventory);
	~Character();

	Inventory* inventory;

	const float& GetMovementSpeed() const;
	const float& GetHP() const;
	float GetGrabRange();
	bool isMoving();

	void SetHP(float value);
	void SetMovementSpeed(float value);

	void MoveVertically();
	void MoveHorizontally();
	/*bool UseLighter(Candle* candle);*/
	bool Interact(int ID, IInteractive* actor);
	bool Interact(Collectable* collectable);
	void OpenInventory(int ID);
	void CloseInventory(int ID);
	bool isBagOpened(int ID);
	void GoToBagSlot(int ID, int slotNumber);
};
#endif
