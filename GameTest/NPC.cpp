#include "stdafx.h"
#include "NPC.h"

NPC::NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* currentScene, float HP, float movementSpeed) 
	: Character(name, sprite, position, collider, currentScene, HP, movementSpeed)
{
}

NPC::~NPC()
{
}


// Play a dialogue
void NPC::PlayDialogue(int dialogueID)
{
	if (!dialogues[dialogueID].first)
	{
		dialogues[dialogueID].first = true;
		std::cout << "[" <<  GetName() << "] says : " << dialogues[dialogueID].second << std::endl;
	}
}

// Stop a dialogue
void NPC::StopDialogue(int dialogueID)
{
	if (dialogues[dialogueID].first)
		dialogues[dialogueID].first = false;
}

// Executing instructions when the NPC is being interacted with
void NPC::Interact()
{
	// Dialogue to play
	PlayDialogue(0);
}
