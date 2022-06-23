#pragma once

#ifndef STATECONTROLLER_H_
#define STATECONTROLLER_H_

class Player;
#include "Player.h"

class StateController
{
public:
	Player* _player;

	virtual ~StateController();
	
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif