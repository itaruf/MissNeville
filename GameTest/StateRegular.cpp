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
	_player->MoveHorizontally();
	_player->MoveVertically();
	_player->IsMoving();
	_player->BagAction();
}

void StateRegular::Render()
{
}

void StateRegular::Exit()
{
}
