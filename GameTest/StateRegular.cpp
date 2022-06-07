#include "stdafx.h"
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
		_player->MoveHorizontally();
		_player->MoveVertically();
		_player->IsMoving();
		_player->BagAction();
		_player->OnCollision();
	}
}

void StateRegular::Render()
{
}

void StateRegular::Exit()
{
}
