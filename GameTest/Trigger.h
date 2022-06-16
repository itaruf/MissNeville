#pragma once
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Actor.h"

class Trigger : public Actor
{
public:
	bool _activated{ true };
	Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated = true);
	virtual ~Trigger();

	virtual void OnOverlap() = 0;
};

#endif