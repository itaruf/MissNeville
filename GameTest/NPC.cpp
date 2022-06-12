#include "stdafx.h"
#include "NPC.h"
#include "StateDialogue.h"

NPC::NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed, Controller* controller)
	: Character(name, sprite, position, collider, HP, movementSpeed, controller)
{
}

NPC::~NPC()
{
}

// Play a dialogue
void NPC::PlayDialogue()
{
	if (_currentDialogue == " ")
		return;

	dynamic_cast<StateDialogue*>(GameState::_currentState)->_currentDialogue = "[" + GetName() + "] says : " + _currentDialogue;
	/*App::Print(100, 100, ("[" + GetName() + "] says : " + _currentDialogue).c_str());
	std::cout << "[" << GetName() << "] says : " << _currentDialogue << std::endl;*/
}

// Play a dialogue
void NPC::PlayDialogue(int dialogueID)
{
	if (!dialogues[dialogueID].first)
		return;

	dialogueID++;
	std::cout << "[" << GetName() << "] says : " << dialogues[dialogueID].second << std::endl;
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
		_currentDialogue = dialogues[dialogueID].second;
}

// Executing instructions when the NPC is being interacted with
void NPC::Interact()
{
	// Dialogue to play
	PlayDialogue();
}
