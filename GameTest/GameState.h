#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

class Scene;
#include "Scene.h"

class Entrance;
#include "Entrance.h"

class Player;
#include "Player.h"

class GameStateController;
#include "GameStateController.h"

enum class State;
#include "EState.h"

// Class in charge of managing the current state of the game and navigating through rooms
class GameState
{
private:
protected:
public:
	static State _state;
	static Scene* _currentScene;
	static std::vector<Scene*> rooms;
	static Player* player;
	static std::vector<GameStateController*> gameStates;
	static GameStateController* currentState;

	GameState();
	~GameState();

	Player* GetPlayer();
	void AddPlayer(Player* player);
	void SwitchState();
	std::string PrintState();

	static void GameState::SetState(State state)
	{
		_state = state;
		switch (state)
		{
		case State::REGULAR:
			currentState = gameStates[0];
			break;

		case State::INVENTORY:
			currentState = gameStates[1];
			break;

		case State::DIALOGUE:
			currentState = gameStates[2];
			break;

		default:
			break;
		}
	}
};

#endif