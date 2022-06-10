#pragma once
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Actor.h"

class Trigger : public Actor
{
public:
	Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	virtual ~Trigger();

	virtual void OnOverlap() = 0;
};

#endif