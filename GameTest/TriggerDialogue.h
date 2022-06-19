#pragma once

#ifndef TRIGGERDIALOGUE_H_
#define TRIGGERDIALOGUE_H_

#include "Trigger.h"
#include "StateMain.h"
#include "StateDialogue.h"

class Scene;

class TriggerDialogue : public Trigger
{
public:
	std::string _dialogue;
	TriggerDialogue(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider = new Collision(16, 16, Collision::ColliderType::Overlap), std::string dialogue = " ", bool activated = true, const char* sfx = SFX.tp_sound);
	~TriggerDialogue();

	void OnOverlap() override;
};

#endif
