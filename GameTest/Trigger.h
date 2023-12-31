#pragma once
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Actor.h"
#include "Utilities.h"

class Trigger : public Actor
{
public:
	bool _activated{ true };
	CSimpleSprite::Anim _anim;

	Delegate _onTriggered;
	Delegate _onActivated;
	Delegate _onDeactivated;

	Trigger(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider = new Collision(16, 16, ColliderType::Overlap), bool activated = true, const char* sfx = SFX.tp_sound);
	virtual ~Trigger();

	virtual void OnOverlap();
	virtual void OnActivation();
	virtual void OnDeactivation();
};

#endif