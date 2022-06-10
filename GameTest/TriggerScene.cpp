#include "stdafx.h"
#include "TriggerScene.h"

TriggerScene::TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Trigger(name, sprite, position, collider), _scene{ nullptr }
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

	if (!v)
		return;

	if (!_collider->isColliding(p, this, v->_x, v->_y))
		return;

	App::Print(350, 350, _name.c_str());

	if (!_scene)
		return;

	GameState::_currentScene = _scene;
	if (!GameState::_currentScene->Init())
		std::cout << GameState::_currentScene->GetID() << " Initialized" << std::endl;
	else
		std::cout << GameState::_currentScene->GetID() << " Already Initialized" << std::endl;
}
