#include "../stdafx.h"
#include "NPC.h"
#include "StateDialogue.h"

NPC::NPC(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, float HP, float movementSpeed, Controller* controller)
	: Character(name, sprite, position, collider, HP, movementSpeed, controller)
{
	_SInteract = SFX.ghost_death;
}

// Play a dialogue
void NPC::PlayDialogue()
{
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	if (_currentDialogue.empty())
		stateDialogue->_currentDialogue.emplace_back("[" + GetName() + "] says : ...");
	else
		stateDialogue->_currentDialogue.emplace_back(_currentDialogue);
}

// Executing instructions when the NPC is being interacted with
void NPC::Interact()
{
	// Dialogue to play
	PlayDialogue();
	CSimpleSound::GetInstance().PlaySoundW(SFX.ghost_death, 0);
}