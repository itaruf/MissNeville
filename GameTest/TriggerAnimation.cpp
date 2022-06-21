#include "../stdafx.h"
#include "TriggerAnimation.h"

TriggerAnimation::TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, bool activated, const char* sfx) : Trigger(name, sprite, position, collider, activated, sfx)
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

	if (!_targetSprite)
		return;

	if (!_targetAnim)
		return;

	_activated = !_activated;

	PlayAnimation();
	
	if (_SInteract == "")
		return;

	if (!CSimpleSound::GetInstance().IsPlaying(_SInteract))
		CSimpleSound::GetInstance().PlaySoundW(_SInteract);

}

void TriggerAnimation::OnActivation()
{
	_activated = true;
}

void TriggerAnimation::PlayAnimation()
{
	_onPlayingAnim();
	_targetSprite->SetAnimation(_targetAnim);
	auto tmp = _targetSprite->GetAnimations()[_targetSprite->GetCurrentAnim()].m_frames;
	if (tmp[_targetSprite->GetFrame()] == tmp[tmp.size() - 1])
	{
		_targetSprite->SetAnimation(-1);
		return;
	}
}
