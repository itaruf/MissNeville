#include "../stdafx.h"
#include "StateRegular.h"

StateRegular::StateRegular()
{
}

StateRegular::~StateRegular()
{
}

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
	}
}

void StateRegular::Render()
{
}

void StateRegular::Exit()
{
}
