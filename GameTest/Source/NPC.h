#pragma once
#ifndef NPC_H_
#define NPC_H_

#include "Character.h"
#include "IInteractive.h"
#include "GameState.h"
#include "StateController.h"
#include "Utilities.h"

#include <unordered_map>

class GameState;
class StateDialogue;

// Class for non-playable entities (very WIP)
class NPC : public Character, public IDialogue, public IInteractive
{
public:
	NPC(std::string name = "" , CSimpleSprite* sprite = nullptr, Vector2D position = (0,0), Collision* collider = nullptr, float HP = 0, float movementSpeed = 0, Controller* controller = nullptr);
	~NPC() = default;

	void PlayDialogue() override;
	void Interact() override;
};

#endif