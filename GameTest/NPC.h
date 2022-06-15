#pragma once
#ifndef NPC_H_
#define NPC_H_

#include "Character.h"
#include "IInteractive.h"
#include <unordered_map>
#include "Utilities.h"
#include "StateMain.h"

//class StateDialogue;
//#include "StateDialogue.h"

class StateController;
#include "StateController.h"

class StateDialogue;

//#include "StateDialogue.h"

// Class for non-playable entities (very WIP)
class NPC : public Character, public IInteractive
{
private:
protected:
public:
	std::string _currentDialogue;
	std::unordered_map<int, std::pair<bool, std::string>> dialogues;

	NPC(std::string name = "" , CSimpleSprite* sprite = nullptr, Vector2D* position = nullptr, Collision* collider = nullptr, float HP = 0, float movementSpeed = 0, Controller* controller = nullptr);
	~NPC();

	void PlayDialogue() override;
	void SetCurrentDialogue(int dialogueID) override;
	void Interact() override;
};

#endif
