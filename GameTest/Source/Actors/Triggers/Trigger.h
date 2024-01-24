#pragma once
#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "../../Actors/Actor.h"
#include "../../Utilities/Utilities.h"

class Trigger : public Actor
{
protected:
	bool _activated{ true };
	CSimpleSprite::Anim _anim;
public:
	Delegate onTriggered;
	Delegate onActivated;
	Delegate onDeactivated;
public:

	Trigger(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider = new Collision(16, 16, ColliderType::Overlap), bool activated = true, const char* sfx = SFX.tp_sound);
	virtual ~Trigger() = default;

	virtual void OnOverlap();
	virtual void OnActivation();
	virtual void OnDeactivation();

	void SetActivation(bool value);
};

#endif