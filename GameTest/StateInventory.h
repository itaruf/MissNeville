#pragma once

#ifndef STATEINVENTORY_H_
#define STATEINVENTORY_H_

#include "GameStateController.h"
class StateInventory : public GameStateController
{
public:
	StateInventory();
	~StateInventory();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

#endif