#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "app\app.h"
#include "EDirection.h"
#include "Candle.h"
#include "Inventory.h"
#include "ICollectable.h"
class GameState;
#include "GameState.h"
//class Candle;

// Class for the player character
class Player : public Character
{
private:
protected:
public:
	Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed, Inventory* inventory);
	~Player();

	Inventory* _inventory;

	void MoveVertically();
	void MoveHorizontally();
	void BagAction();
	bool Interact(IInteractive* actor);
	bool Interact(Collectable* collectable);
	void OpenBag(int ID);
	void CloseBag(int ID);
	void GoToBagSlot(int ID, int slotNumber);
	void Interaction();
};
#endif
