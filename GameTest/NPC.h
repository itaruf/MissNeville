#pragma once
#ifndef NPC_H_
#define NPC_H_

#include "Character.h"
#include "IDialogue.h"
#include "IInteractive.h"

class NPC : public Character, public IDialogue, public IInteractive
{
private:
protected:
public:
	static int dialogueID;
	std::string currentDialogue;
	std::map<int, std::pair<bool, std::string>> dialogues;

	NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed);
	~NPC();

	void PlayDialogue(int dialogueID) override;
	void StopDialogue(int dialogueID) override;
	void Interact() override;
};

#endif
