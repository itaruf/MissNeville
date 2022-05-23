#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "app\app.h"
#include "EDirection.h"
#include "Candle.h"
#include "Inventory.h"
#include "ICollectable.h"

//class Candle;

// Class for the player character
class Player : public Character
{
private:
protected:
public:
	Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* currentScene, float HP, float movementSpeed, Inventory* inventory);
	~Player();

	Inventory* inventory;

	void MoveVertically();
	void MoveHorizontally();
	bool Interact(IInteractive* actor);
	bool Interact(Collectable* collectable);
	void OpenBag(int ID);
	void CloseBag(int ID);
	void GoToBagSlot(int ID, int slotNumber);
};
#endif
