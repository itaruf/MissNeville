#include "../stdafx.h"
#include "Trigger.h"

Trigger::Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated, const char* sfx) : Actor(name, sprite, position, collider), _activated{activated}
{
	_SInteract = sfx;
}

Trigger::~Trigger()
{
}

void Trigger::OnOverlap()
{
	if (!_activated)
		return;

	if (!_collider)
		return;

	if (!_collider->isOverlapping(StateMain::_player, this))
		return;
	
	_onTriggered();
	_activated = false;
}

void Trigger::OnActivation()
{
	if (_activated)
		return;

	_onActivated();
	_activated = true;
	CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
}

void Trigger::OnDeactivation()
{
	if (!_activated)
		return;

	_onDeactivated();
	_activated = false;
	CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
}
