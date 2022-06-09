#pragma once

#ifndef TRIGGERSCENE_H_
#define TRIGGERSCENE_H_

#include "Trigger.h"
#include "GameState.h"

class TriggerScene : public Trigger
{
public:
	Scene* _scene;
	TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~TriggerScene();

	void OnOverlap() override;
};

#endif
