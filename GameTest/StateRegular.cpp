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
}

void StateRegular::Render()
{
}

void StateRegular::Exit()
{
}
