#pragma once

#ifndef GAMESTATECONTROLLER_H_
#define GAMESTATECONTROLLER_H_

#include <vector>

class Player;
#include "Player.h"

class GameStateController
{
public:
	Player* _player;
	virtual ~GameStateController();
	
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif