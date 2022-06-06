#pragma once

#include "GameStateController.h"

class Player;
#include "Player.h";

class StateRegular : public GameStateController
{
public:

	Player* player;
	StateRegular();
	~StateRegular();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

