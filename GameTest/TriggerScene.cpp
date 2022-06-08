#include "stdafx.h"
#include "TriggerScene.h"

TriggerScene::TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Trigger(name, sprite, position, collider)
{
}

TriggerScene::~TriggerScene()
{
}
