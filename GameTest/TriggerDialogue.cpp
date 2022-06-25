#include "../stdafx.h"
#include "TriggerDialogue.h"

TriggerDialogue::TriggerDialogue(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, std::string dialogue, bool activated, const char* sfx) : Trigger(name, sprite, position, collider, activated, sfx), _dialogue{ dialogue }
{
}

TriggerDialogue::~TriggerDialogue()
{
}

void TriggerDialogue::OnOverlap()
{
	if (!_activated)
		return;

	if (!_collider)
		return;

	if (!_collider->isOverlapping(StateMain::_player, this))
		return;

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(_dialogue);
	StateMain::SetState(State::DIALOGUE);
	_activated = false;
}

void TriggerDialogue::OnActivation()
{
	_activated = true;
}
