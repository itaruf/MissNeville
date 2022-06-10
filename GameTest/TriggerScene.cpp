#include "stdafx.h"
#include "TriggerScene.h"

TriggerScene::TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Trigger(name, sprite, position, collider)
{
}

TriggerScene::~TriggerScene()
{
	if (_scene)
		delete _scene;
}

void TriggerScene::OnOverlap()
{
	if (!_collider)
		return;

	if (!GameState::_player)
		return;

	auto p = GameState::_player;
	auto v = p->GetPosition();

	if (
		_collider->isColliding(p, this, v->_x, v->_y + p->GetMovementSpeed()) ||
		_collider->isColliding(p, this, v->_x, v->_y - p->GetMovementSpeed()) ||
		_collider->isColliding(p, this, v->_x + p->GetMovementSpeed(), v->_y) ||
		_collider->isColliding(p, this, v->_x - p->GetMovementSpeed(), v->_y)
		)
	{
		App::Print(350, 350, _name.c_str());

		if (!_scene)
			return;

		GameState::_currentScene = _scene;
	}
}
