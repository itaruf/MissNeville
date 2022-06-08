#pragma once

#ifndef TRIGGERSCENE_H_
#define TRIGGERSCENE_H_

#include "Trigger.h"

class TriggerScene : public Trigger
{
public:
	TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~TriggerScene();
};

#endif
