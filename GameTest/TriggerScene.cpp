#include "../stdafx.h"
#include "TriggerScene.h"

TriggerScene::~TriggerScene()
{
	if (_scene)
		delete _scene;
}

void TriggerScene::OnActivation()
{
	if (_activated)
		return;

	CSimpleSound::GetInstance().PlaySoundW(_SInteract);
	_activated = true;
}

TriggerScene::TriggerScene(std::string name, CSimpleSprite* sprite, Vector2D* position, Vector2D* playerPos, Collision* collider, Scene* scene, bool activated, const char* sfx) : Trigger(name, sprite, position, collider, activated, sfx), _scene{ scene }, _playerPos{ playerPos }
{
}

void TriggerScene::OnOverlap()
{
	if (!_activated)
		return;

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

	if (_scene)
	{
		StateMain::LoadScene(_scene);

		if (StateMain::_currentScene->initialized)
			std::cout << StateMain::_currentScene->GetID() << " Initialized" << std::endl;
		else
			std::cout << StateMain::_currentScene->GetID() << " Already Initialized" << std::endl;
	}

	if (!_playerPos)
		return;

	p->SetPosition(_playerPos->_x, _playerPos->_y);

	std::cout << "triggered " << std::endl;
	if (_SInteract == "")
		return;

	/*_sprite->SetAnimation(_anim);*/

	/*if (!CSimpleSound::GetInstance().IsPlaying(_SInteract))*/
		CSimpleSound::GetInstance().PlaySoundW(_SInteract);
}
