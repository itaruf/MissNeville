#pragma once
#include <vector>
class GameStateController
{
public:
	std::vector<GameStateController*> gameStates;
	GameStateController();
	virtual ~GameStateController() = default;
	
	virtual void Enter();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

