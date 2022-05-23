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
void NPC::PlayDialogue()
{
	if (currentDialogue != "")
		std::cout << "[" << GetName() << "] says : " << currentDialogue << std::endl;
}

// Play a dialogue
void NPC::PlayDialogue(int dialogueID)
{
	if (dialogues[dialogueID].first)
	{
		dialogueID++;
		std::cout << "[" <<  GetName() << "] says : " << dialogues[dialogueID].second << std::endl;
	}
}

// Stop a specific dialogue
void NPC::StopDialogue(int dialogueID)
{
	if (dialogues[dialogueID].first)
		dialogues[dialogueID].first = false;
}

// Enable of a specific dialogue 
void NPC::EnableDialogue(int dialogueID)
{
	if (!dialogues[dialogueID].first)
		dialogues[dialogueID].first = true;
}

// Set the current dialogue with another dialogue
void NPC::SetCurrentDialogue(int dialogueID)
{
	if (dialogues.find(dialogueID) != dialogues.end())
		currentDialogue = dialogues[dialogueID].second;
}

// Executing instructions when the NPC is being interacted with
void NPC::Interact()
{
	// Dialogue to play
	PlayDialogue();
}
