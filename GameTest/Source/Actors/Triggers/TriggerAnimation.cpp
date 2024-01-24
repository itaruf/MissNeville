#include "../stdafx.h"
#include "TriggerAnimation.h"

TriggerAnimation::TriggerAnimation(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, bool activated, const char* sfx) : Trigger(name, sprite, position, collider, activated, sfx)
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

	if (!_collider->isOverlapping(StateController::_player, this))
		return;

	if (!targetSprite)
		return;

	if (!targetAnim)
		return;

	_activated = !_activated;

	PlayAnimation();
	onTriggered();

	if (_SInteract == "")
		return;

	if (!CSimpleSound::GetInstance().IsPlaying(_SInteract))
		CSimpleSound::GetInstance().PlaySoundW(_SInteract);

}

void TriggerAnimation::OnActivation()
{
	SetActivation(true);
}

void TriggerAnimation::PlayAnimation()
{
	onPlayingAnim();
	targetSprite->SetAnimation(targetAnim);
	auto tmp = targetSprite->GetAnimations()[targetSprite->GetCurrentAnim()].m_frames;
	if (tmp[targetSprite->GetFrame()] == tmp[tmp.size() - 1])
	{
		targetSprite->SetAnimation(-1);
		return;
	}
}