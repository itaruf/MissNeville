#pragma once
#include "GameStateController.h"
#include "GameState.h"
class StateInventory : public GameStateController
{
public:
	Player* player;
	StateInventory();
	~StateInventory();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

