#include "../stdafx.h"
#include "Trigger.h"

Trigger::Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated, const char* sfx) : Actor(name, sprite, position, collider), _activated{activated}
{
	_SInteract = sfx;
}

Trigger::~Trigger()
{
}
