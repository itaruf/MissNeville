#pragma once

#include "GameStateController.h"
class StateRegular : public GameStateController
{
public:
	StateRegular();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

