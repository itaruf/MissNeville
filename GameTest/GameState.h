#pragma once

#ifndef GameState_H_
#define GameState_H_

class Player;
#include "Player.h"

class GameState
{
public:
	Player* _player;
public:
	virtual ~GameState() = default;
	
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif