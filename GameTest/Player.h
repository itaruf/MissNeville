#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Inventory.h"
#include "ICollectable.h"
#include "GameState.h"

// Class for the player character
class Player : public Character
{
private:
protected:
public:
	Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed, Inventory* inventory);
	~Player();

	Inventory* _inventory;

	void MoveVertically() override;
	void MoveHorizontally() override;
	bool Interact(IInteractive* actor);
	bool Interact(Collectable* collectable);
	void OpenBag(int ID);
	void CloseBag(int ID);
	void GoToBagSlot(int ID, int slotNumber);
	void Interaction();
};
#endif
