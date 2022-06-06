#include "stdafx.h"
#include "GameState.h"

Scene* GameState::_currentScene;
std::vector<Scene*> GameState::rooms;
Player* GameState::player;
State GameState::_state;
std::vector<GameStateController*> GameState::gameStates;
GameStateController* GameState::currentState;

GameState::GameState()
{
}


GameState::~GameState()
{
	printf("GAME STATE DESTRUCTOR CALLED\n");

	if (player)
	{
		delete player;
		nullptr;
	}

	/*if (_currentScene)
	{
		delete _currentScene;
		_currentScene = nullptr;
	}*/

	for (auto& room : rooms) 
	{
		if (room)
		{
			delete room;
			room = nullptr;
		}
	}
	rooms.clear();

	for (auto& gameState : gameStates)
		if (gameState)
			delete gameState;

	gameStates.clear();
}

void GameState::AddPlayer(Player* player)
{
	this->player = player;
	player = nullptr;
}

void GameState::SwitchState()
{
	switch (_state)
	{
	case State::REGULAR:
		// Start button to open the inventory / change the state back to INVENTORY
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			std::cout << "Inventory State" << std::endl;
			_state = State::INVENTORY;
			currentState = gameStates[1];
		}
		break;

	case State::DIALOGUE:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			std::cout << "Regular State" << std::endl;
			_state = State::REGULAR;
			currentState = gameStates[0];
		}
		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			std::cout << "Regular State" << std::endl;
			_state = State::REGULAR;
			currentState = gameStates[0];
		}
		break;
	default:
		break;
	}
}

Player* GameState::GetPlayer()
{
	return player;
}

std::string GameState::PrintState()
{
	switch (_state)
	{
	case State::REGULAR:
		return "REGULAR";

	case State::DIALOGUE:
		return "DIALOGUE";

	case State::INVENTORY:
		return "INVENTORY";

	default:
		break;
	}
	return "NO STATE FOUND";

}