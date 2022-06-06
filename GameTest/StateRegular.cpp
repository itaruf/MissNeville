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
	player->MoveHorizontally();
	player->MoveVertically();
	player->IsMoving();
	player->BagAction();
}

void StateRegular::Render()
{
}

void StateRegular::Exit()
{
}
