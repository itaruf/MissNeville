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
class StateDialogue;
#include "StateDialogue.h"
#include "EState.h"

#include "PlayerController.h"
#include "ObjectController.h"

// Class in charge of managing the current state of the game and navigating through rooms
class StateMain
{
private:
protected:
public:

	struct Delegate
	{
		std::vector<std::function<void()>> funcs;
		template<class T> Delegate& operator+=(T mFunc) { funcs.push_back(mFunc); return *this; }
		void operator()() { for (auto& f : funcs) f(); }
	};

	static Delegate delegate;

	static State _state;
	static Scene* _currentScene;
	static std::unordered_map<int, Scene*> _rooms;
	static Player* _player;
	static std::vector<StateController*> _stateControllers;
	static StateController* _currentStateController;

	StateMain();
	~StateMain();

	Player* GetPlayer();
	void SetPlayer(Player* player);
	void SwitchState();
	std::string PrintState();

	static void LoadScene(int ID)
	{
		_currentScene->Exit();
		SetState(State::REGULAR);
		_currentScene = _rooms[ID];
		_currentScene->Init();
	}

	static void LoadScene(Scene* scene)
	{
		_currentScene->Exit();
		SetState(State::REGULAR);
		_currentScene = scene;
		_currentScene->Init();
	}

	static void StateMain::SetState(State state)
	{
		switch (state)
		{
		case State::REGULAR:
			_currentStateController->Exit();
			break;

		case State::INVENTORY:
			_currentStateController->Exit();
			break;

		case State::DIALOGUE:
			_currentStateController->Exit();
			break;

		default:
			break;
		}

		_state = state;
		switch (_state)
		{
		case State::REGULAR:
			_currentStateController = _stateControllers[0];
			_currentStateController->Enter();
			break;

		case State::INVENTORY:;
			_currentStateController = _stateControllers[1];
			_currentStateController->Enter();
			break;

		case State::DIALOGUE:
			_currentStateController = _stateControllers[2];
			_currentStateController->Enter();
			break;

		default:
			break;
		}
	}
};

#endif