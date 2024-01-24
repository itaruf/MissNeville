#include "../stdafx.h"
#include "StateRegular.h"

void StateRegular::Enter()
{
}

void StateRegular::Update()
{
	if (_player)
	{
		_player->GetController()->MoveHorizontally(_player);
		_player->GetController()->MoveVertically(_player);
		_player->IsMoving();
		_player->Interaction();
		_player->Hit();
	}
}

void StateRegular::Render()
{
	if (_player)
	{
		_player->DisplayIcon(_player->_interactSprite);
	}
}

void StateRegular::Exit()
{
}