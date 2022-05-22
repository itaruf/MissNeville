#include "stdafx.h"
#include "NPC.h"

NPC::NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed) 
	: Character(name, sprite, position, collider, currentRoom, HP, movementSpeed)
{
}

NPC::~NPC()
{
}

void NPC::PlayDialogue(int dialogueID)
{
	if (!dialogues[dialogueID].first)
	{
		dialogues[dialogueID].first = true;
		std::cout << "[" <<  GetName() << "] says : " << dialogues[dialogueID].second << std::endl;
	}
}

void NPC::StopDialogue(int dialogueID)
{
	if (dialogues[dialogueID].first)
		dialogues[dialogueID].first = false;
}

void NPC::Interact()
{
	PlayDialogue(0);
}
