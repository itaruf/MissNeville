#pragma once
#ifndef NPC_H_
#define NPC_H_

#include "Character.h"
#include "IDialogue.h"
#include "IInteractive.h"
#include <unordered_map>

// Class for non-playable entities (very WIP)
class NPC : public Character, public IDialogue, public IInteractive
{
private:
protected:
public:
	std::string currentDialogue;
	std::unordered_map<int, std::pair<bool, std::string>> dialogues;

	NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed);
	~NPC();

	void PlayDialogue() override;
	void PlayDialogue(int dialogueID) override;
	void StopDialogue(int dialogueID) override;
	void EnableDialogue(int dialogueID) override;
	void SetCurrentDialogue(int dialogueID) override;
	void Interact() override;
};

#endif
