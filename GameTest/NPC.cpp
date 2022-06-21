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
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
	if (!stateDialogue)
		return;

	if (_currentDialogue.empty())
		stateDialogue->_currentDialogue = "[" + GetName() + "] says : ...";
	else
		stateDialogue->_currentDialogue = "[" + GetName() + "] says : " + _currentDialogue;
}

// Executing instructions when the NPC is being interacted with
void NPC::Interact()
{
	// Dialogue to play
	PlayDialogue();
}

void NPC::OnInteract()
{
}
