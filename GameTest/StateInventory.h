#pragma once

#ifndef STATEINVENTORY_H_
#define STATEINVENTORY_H_

#include "GameStateController.h"
class StateInventory : public GameStateController
{
public:
	int _currentSlot = 0;
	Color selected{ 0, 0, 0 };
	StateInventory();
	~StateInventory();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
	void Navigation();
	void Select();
};

#endif