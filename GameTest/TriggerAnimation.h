#pragma once

#ifndef TRIGGERANIMATION_H_
#define TRIGGERANIMATION_H_

#include "Trigger.h"
#include "StateMain.h"

class Scene;

class TriggerAnimation : public Trigger
{
public:
	CSimpleSprite::Anim _targetAnim;
	CSimpleSprite* _targetSprite;
	TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated = false, const char* sfx = SFX.tp_sound);
	~TriggerAnimation();

	void OnOverlap() override;
};

#endif
