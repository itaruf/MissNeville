#include "../stdafx.h"
#include "Button.h"

Button::Button(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, bool activated) : Actor(name, sprite, position, collider), _activated{activated}
{
	_SInteract = SFX.candle_enlight;
}

bool Button::isActivated()
{
	return _activated;
}

void Button::Interact()
{
	if (!_activated)
	{
		CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
		_activated = true;
		onActivated();
		_sprite->SetFrame(1);
	}
	else
	{
		CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
		_activated = false;
		onDeactivated();
		_sprite->SetFrame(0);
	}
}