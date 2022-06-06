#pragma once
#ifndef STATEREGULAR_H_
#define STATEREGULAR_H_

class GameStateController;
#include "GameStateController.h"

class StateRegular : public GameStateController
{
public:

	StateRegular();
	~StateRegular();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

#endif 