#pragma once

#ifndef TRIGGERANIMATION_H_
#define TRIGGERANIMATION_H_

#include "Trigger.h"
#include "StateController.h"

class Scene;

class TriggerAnimation : public Trigger
{
public:
	Delegate _onPlayingAnim;

	CSimpleSprite::Anim _targetAnim;
	CSimpleSprite* _targetSprite;
	TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider = new Collision(32, 32, ColliderType::Overlap), bool activated = false, const char* sfx = SFX.tp_sound);
	~TriggerAnimation();

	void OnOverlap() override;
	void OnActivation() override;
	void PlayAnimation();
};

#endif
