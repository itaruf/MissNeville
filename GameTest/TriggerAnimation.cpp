#include "../stdafx.h"
#include "TriggerAnimation.h"

TriggerAnimation::TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Trigger(name, sprite, position, collider)
{
}

TriggerAnimation::~TriggerAnimation()
{
}

void TriggerAnimation::OnOverlap()
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

	_activated = false;

	if (!_targetSprite)
		return;

	_targetSprite->SetAnimation(_anim);
	auto tmp = _targetSprite->GetAnimations()[_targetSprite->GetCurrentAnim()].m_frames;
	if (tmp[_targetSprite->GetFrame()] == tmp[tmp.size() - 1])
	{
		_targetSprite->SetAnimation(-1);
		return;
	}
	
	if (_sfx == "")
		return;

	if (!CSimpleSound::GetInstance().IsPlaying(_sfx))
		CSimpleSound::GetInstance().PlaySoundW(_sfx);
}
