#include "../stdafx.h"
#include "Trigger.h"

Trigger::Trigger(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, bool activated, const char* sfx) : Actor(name, sprite, position, collider), _activated{activated}
{
	_SInteract = sfx;
}

void Trigger::OnOverlap()
{
	if (!_activated)
		return;

	if (!_collider)
		return;

	if (!_collider->isOverlapping(StateController::_player, this))
		return;
	
	onTriggered();
	SetActivation(false);
}

void Trigger::OnActivation()
{
	if (_activated)
		return;

	onActivated();
	SetActivation(true);
	CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
}

void Trigger::OnDeactivation()
{
	if (!_activated)
		return;

	onDeactivated();
	SetActivation(false);
	CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
}

void Trigger::SetActivation(bool value)
{
	_activated = value;
}