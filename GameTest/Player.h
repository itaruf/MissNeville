#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Inventory.h"
#include "ICollectable.h"
#include "StateMain.h"

// Class for the player character
class Player : public Character, public IDialogue
{
private:
protected:
public:
	friend class PlayerController;
	/*CSimpleSound* _SFXBag{ nullptr };
	CSimpleSound* _SFXCollect{ nullptr };*/
	
	const char* _SBag{SFX.candle_enlight};
	const char* _SCollect{SFX.item_pick};

	Player(std::string name = "", CSimpleSprite* sprite = nullptr, Vector2D* position = nullptr, Collision* collider = nullptr, float HP = 0, float movementSpeed = 0, Controller* controller = nullptr, Inventory* inventory = nullptr);
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

	void PlayDialogue() override;
};
#endif
