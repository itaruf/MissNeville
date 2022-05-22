#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "app\app.h"
#include "EDirection.h"
#include "Candle.h"
#include "Inventory.h"
#include "ICollectable.h"

class Candle;
class Player : public Character
{
private:
protected:
	float grabRange{ 500 };
public:
	Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed, Inventory* inventory);
	~Player();

	Inventory* inventory;

	float GetGrabRange();
	bool isMoving();

	void MoveVertically();
	void MoveHorizontally();
	/*bool UseLighter(Candle* candle);*/
	bool Interact(IInteractive* actor);
	bool Interact(Collectable* collectable);
	void OpenInventory(int ID);
	void CloseInventory(int ID);
	void GoToBagSlot(int ID, int slotNumber);
};
#endif
