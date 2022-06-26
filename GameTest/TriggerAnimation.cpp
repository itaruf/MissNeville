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

	if (!_collider->isOverlapping(StateMain::_player, this))
		return;

	if (!_targetSprite)
		return;

	if (!_targetAnim)
		return;

	_activated = !_activated;

	PlayAnimation();
	_onTriggered();

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
