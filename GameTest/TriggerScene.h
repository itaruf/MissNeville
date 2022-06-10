#pragma once

#ifndef TRIGGERSCENE_H_
#define TRIGGERSCENE_H_

#include "Trigger.h"
#include "GameState.h"

class TriggerScene : public Trigger
{
public:
	Scene* _scene;
	Vector2D* _playerPos;
	TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* scene, Vector2D* playerPos);
	~TriggerScene();

	void OnOverlap() override;
};

#endif
