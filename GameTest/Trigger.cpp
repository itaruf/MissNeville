#include "../stdafx.h"
#include "Trigger.h"

Trigger::Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated) : Actor(name, sprite, position, collider), _activated{activated}
{
}

Trigger::~Trigger()
{
}
