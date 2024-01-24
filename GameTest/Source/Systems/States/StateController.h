#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "../../Controllers/ObjectController.h"
#include "../../Controllers/PlayerController.h"
#include "../../Enums/EState.h"
#include "../../Scenes/Entrance.h"
#include "../../Systems/States/StateDialogue.h"
#include "../../Utilities/Utilities.h"

#include <chrono>
#include <thread>
#include <future>

class GameState;
class Player;
class Scene;
class StateDialogue;

// Class in charge of managing the current state of the game and navigating through rooms
class StateController
{
public:
	static Delegate delegate;

	static State _state;

	static Scene* _currentScene;
	static std::unordered_map<int, Scene*> _rooms;

	static Player* _player;

	static std::vector<GameState*> _gameStates;
	static GameState* _currentGameState;
public:

	StateController() = default;
	~StateController();

	Player* GetPlayer();
	void SetPlayer(Player* player);
	void SwitchState();
	std::string PrintState();

	static void LoadScene(int ID)
	{
		_currentScene->Exit();
		_currentScene = _rooms[ID];
		_currentScene->Init();
	}

	static void LoadScene(Scene* scene)
	{
		_currentScene->Exit();
		_currentScene = scene;
		std::cout << scene->GetID() << std::endl;
		_currentScene->Init();
	}

	static void StateController::SetState(State state)
	{
		switch (state)
		{
		case State::REGULAR:
			_currentGameState->Exit();
			break;

		case State::INVENTORY:
			_currentGameState->Exit();
			break;

		case State::DIALOGUE:
			_currentGameState->Exit();
			break;

		default:
			break;
		}

		_state = state;
		switch (_state)
		{
		case State::REGULAR:
			_currentGameState = _gameStates[0];
			_currentGameState->Enter();
			break;

		case State::INVENTORY:;
			_currentGameState = _gameStates[1];
			_currentGameState->Enter();
			break;

		case State::DIALOGUE:
			_currentGameState = _gameStates[2];
			_currentGameState->Enter();
			break;

		default:
			break;
		}
	}
};

#endif