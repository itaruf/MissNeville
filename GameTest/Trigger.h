#pragma once
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Actor.h"

class Trigger : public Actor
{
public:
	bool _activated{ true };
	CSimpleSprite::Anim _anim;

	Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated = true, const char* sfx = SFX.tp_sound);
	virtual ~Trigger();

	virtual void OnOverlap() = 0;
};

#endif