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

	_onActivated();
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

	if (!_collider->isOverlapping(StateController::_player, this))
		return;

	if (_scene)
	{
		StateController::LoadScene(_scene);

		if (StateController::_currentScene->initialized)
			std::cout << StateController::_currentScene->GetID() << " Initialized" << std::endl;
		else
			std::cout << StateController::_currentScene->GetID() << " Already Initialized" << std::endl;
	}

	if (!_playerPos)
		return;

	StateController::_player->SetPosition(_playerPos->_x, _playerPos->_y);

	if (_SInteract == "")
		return;

	/*_sprite->SetAnimation(_anim);*/

	/*if (!CSimpleSound::GetInstance().IsPlaying(_SInteract))*/
		CSimpleSound::GetInstance().PlaySoundW(_SInteract);
}
