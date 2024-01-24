#pragma once

#ifndef STATEINVENTORY_H_
#define STATEINVENTORY_H_

#include "GameState.h"

class StateInventory : public GameState
{
public:
	int _currentSlot = 0;
	Color selected{ 0, 0, 0 };

	const char* _SBag_open{SFX.item_pick2};
	const char* _SBag_navigate{ SFX.bag_navigate };
public:
	StateInventory() = default;
	~StateInventory() = default;

	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;

	void Navigation();
	void Select();
};

#endif