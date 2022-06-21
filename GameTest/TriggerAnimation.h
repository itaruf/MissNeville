#pragma once

#ifndef TRIGGERANIMATION_H_
#define TRIGGERANIMATION_H_

#include "Trigger.h"
#include "StateMain.h"

class Scene;

class TriggerAnimation : public Trigger
{
public:
	struct Delegate
	{
		std::vector<std::function<void()>> funcs;
		template<class T> Delegate& operator+=(T mFunc) { funcs.push_back(mFunc); return *this; }
		void operator()() { for (auto& f : funcs) f(); }
	};

	Delegate _onPlayingAnim;

	CSimpleSprite::Anim _targetAnim;
	CSimpleSprite* _targetSprite;
	TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider = new Collision(32, 32, Collision::ColliderType::Overlap), bool activated = false, const char* sfx = SFX.tp_sound);
	~TriggerAnimation();

	void OnOverlap() override;
	void OnActivation() override;
	void PlayAnimation();
};

#endif
