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

	if (!StateMain::_player)
		return;

	auto p{ StateMain::_player };
	auto v{ p->GetPosition() };

	if (!v)
		return;

	if (!_collider->isColliding(p, this, v->_x, v->_y))
		return;

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue = _dialogue;
	StateMain::SetState(State::DIALOGUE);
	_activated = !_activated;
}
