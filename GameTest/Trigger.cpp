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

	if (!StateMain::_player)
		return;

	auto p{ StateMain::_player };
	auto v{ p->GetPosition() };

	if (!v)
		return;

	if (!_collider->isColliding(p, this, v->_x, v->_y))
		return;

	_onTriggered();

	_activated = false;
}

void Trigger::OnActivation()
{
}
