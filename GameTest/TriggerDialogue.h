#pragma once

#ifndef TRIGGERDIALOGUE_H_
#define TRIGGERDIALOGUE_H_

#include "StateController.h"
#include "StateDialogue.h"
#include "Trigger.h"

class Scene;

class TriggerDialogue : public Trigger
{
private:
	std::string _dialogue;
public:
	TriggerDialogue(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider = new Collision(16, 16, ColliderType::Overlap), std::string dialogue = " ", bool activated = true, const char* sfx = SFX.tp_sound);
	~TriggerDialogue();

	void OnOverlap() override;
	void OnActivation() override;
};

#endif
