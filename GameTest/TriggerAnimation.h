#pragma once

#ifndef TRIGGERANIMATION_H_
#define TRIGGERANIMATION_H_

#include "StateController.h"
#include "Trigger.h"

class Scene;

class TriggerAnimation : public Trigger
{
public:
	Delegate onPlayingAnim;

	CSimpleSprite::Anim targetAnim;
	CSimpleSprite* targetSprite;
public:
	TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider = new Collision(32, 32, ColliderType::Overlap), bool activated = false, const char* sfx = SFX.tp_sound);
	~TriggerAnimation();

	void OnOverlap() override;
	void OnActivation() override;

	void PlayAnimation();
};

#endif