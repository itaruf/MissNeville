#include "../stdafx.h"
#include "TriggerScene.h"

TriggerScene::~TriggerScene()
{
	if (_scene)
		delete _scene;
}

TriggerScene::TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* scene, Vector2D* playerPos) : Trigger(name, sprite, position, collider), _scene{ scene }, _playerPos{ playerPos }
{
}

void TriggerScene::OnOverlap()
{
	if (!_collider)
		return;

	if (!StateMain::_player)
		return;

	auto p{ StateMain::_player };
	auto v{ p->GetPosition() };

	if (!v)
		return;

	if (!_collider->isColliding(p, this, v->_x, v->_y))
		return;

	App::Print(350, 350, _name.c_str());

	if (!_scene)
	{
		std::cout << "null" << std::endl;
		return;
	}

	StateMain::_currentScene = _scene;

	if (!StateMain::_currentScene->Init())
		std::cout << StateMain::_currentScene->GetID() << " Initialized" << std::endl;
	else
		std::cout << StateMain::_currentScene->GetID() << " Already Initialized" << std::endl;

	if (!_playerPos)
		return;

	/*std::cout << _playerPos->_x << std::endl;
	std::cout << _playerPos->_y << std::endl;*/

	p->SetPosition(_playerPos->_x, _playerPos->_y);
}
