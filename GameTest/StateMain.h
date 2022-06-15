#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <chrono>
#include <thread>
#include <future>

#include "Entrance.h"
class Scene;
class Player;
class StateController;
#include "EState.h"

#include "PlayerController.h"
#include "ObjectController.h"

// Class in charge of managing the current state of the game and navigating through rooms
class StateMain
{
private:
protected:
public:
	static State _state;
	static Scene* _currentScene;
	static std::vector<Scene*> _rooms;
	static Player* _player;
	static std::vector<StateController*> _stateControllers;
	static StateController* _currentStateController;

	StateMain();
	~StateMain();

	Player* GetPlayer();
	void AddPlayer(Player* player);
	void SwitchState();
	std::string PrintState();
	void OnChangeState();

	static void StateMain::SetState(State state)
	{
		_state = state;
		switch (state)
		{
		case State::REGULAR:
			_currentStateController = _stateControllers[0];
			break;

		case State::INVENTORY:
			_currentStateController = _stateControllers[1];
			break;

		case State::DIALOGUE:
			_currentStateController = _stateControllers[2];
			break;

		default:
			break;
		}
	}
};

#endif