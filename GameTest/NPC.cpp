#include "../stdafx.h"
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
	/*if (_currentDialogue == " ")
		return;*/

	StateMain::SetState(State::DIALOGUE);

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_currentStateController) };
	if (!stateDialogue)
		return;
	stateDialogue->_currentDialogue = "[" + GetName() + "] says : " + _currentDialogue;
	stateDialogue->Enter();
}

/*
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

*/
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
