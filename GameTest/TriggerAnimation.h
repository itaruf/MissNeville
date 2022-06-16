#pragma once

#ifndef TRIGGERANIMATION_H_
#define TRIGGERANIMATION_H_

#include "Trigger.h"
#include "StateMain.h"

class Scene;

class TriggerAnimation : public Trigger
{
public:
	CSimpleSprite::Anim _anim;
	CSimpleSprite* _targetSprite;
	const char* _sfx;
	bool _end{ false };
	TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~TriggerAnimation();

	void OnOverlap() override;
};

#endif
