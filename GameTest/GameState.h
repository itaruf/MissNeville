#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <chrono>
#include <thread>
#include <future>

#include "Entrance.h"
class Scene;
class Player;
class GameStateController;
#include "EState.h"

#include "PlayerController.h"
#include "ObjectController.h"

// Class in charge of managing the current state of the game and navigating through rooms
class GameState
{
private:
protected:
public:
	static State _state;
	static Scene* _currentScene;
	static std::vector<Scene*> _rooms;
	static Player* _player;
	static std::vector<GameStateController*> _gameStates;
	static GameStateController* _currentState;

	GameState();
	~GameState();

	Player* GetPlayer();
	void AddPlayer(Player* player);
	void SwitchState();
	std::string PrintState();
	void OnChangeState();

	static void GameState::SetState(State state)
	{
		_state = state;
		switch (state)
		{
		case State::REGULAR:
			_currentState = _gameStates[0];
			break;

		case State::INVENTORY:
			_currentState = _gameStates[1];
			break;

		case State::DIALOGUE:
			_currentState = _gameStates[2];
			break;

		default:
			break;
		}
	}
};

#endif