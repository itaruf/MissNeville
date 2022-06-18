#pragma once

#ifndef TRIGGERSCENE_H_
#define TRIGGERSCENE_H_

#include "Trigger.h"
#include "StateMain.h"

class Scene;

class TriggerScene : public Trigger
{
public:
	Scene* _scene;
	Vector2D* _playerPos;
	TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Vector2D* playerPos = new Vector2D(), Collision* collider = new Collision(32, 32), Scene* scene = nullptr, bool activated = true, const char* sfx = SFX.tp_sound);
	~TriggerScene();

	void OnOverlap() override;
};

#endif
