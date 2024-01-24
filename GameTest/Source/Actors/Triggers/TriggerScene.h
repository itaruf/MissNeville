#pragma once

#ifndef TRIGGERSCENE_H_
#define TRIGGERSCENE_H_

#include "../../Systems/States/StateController.h"

#include "Trigger.h"

class Scene;

class TriggerScene : public Trigger
{
public:
	Scene* _scene;
	Vector2D _playerPos;
public:
	TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D position, Vector2D playerPos = Vector2D(0,0), Collision* collider = new Collision(16, 16, ColliderType::Overlap), Scene* scene = nullptr, bool activated = true, const char* sfx = SFX.door_open);
	~TriggerScene();

	void OnOverlap() override;
	void OnActivation() override;
};

#endif
