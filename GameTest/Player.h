#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Inventory.h"
#include "ICollectable.h"
#include "StateController.h"

// Class for the player character
class Player : public Character, public IDialogue
{
private:
	const char* _SBag{SFX.candle_enlight};
	const char* _SCollect{SFX.item_pick};
	const char* _SHit{ SFX.candle_enlight };

public:
	friend class PlayerController;

	CSimpleSprite* _interactSprite;

	Inventory* _inventory;
public:
	Player(std::string name = "", CSimpleSprite* sprite = nullptr, Vector2D position = (0,0), Collision* collider = nullptr, float HP = 0, float movementSpeed = 0, Controller* controller = nullptr, Inventory* inventory = nullptr);
	~Player();

	void MoveVertically() override;
	void MoveHorizontally() override;
	void PlayDialogue() override;

	bool Interact(IInteractive* actor);
	bool Interact(Collectable* collectable);
	void Interaction();

	void OpenBag(int ID);
	void CloseBag(int ID);
	void GoToBagSlot(int ID, int slotNumber);

	void DisplayIcon(CSimpleSprite* icon);

	void Hit();

	void Respawn(Vector2D newPos);
};
#endif