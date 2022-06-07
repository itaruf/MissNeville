#include "stdafx.h"
#include "GameState.h"

Scene* GameState::_currentScene;
std::vector<Scene*> GameState::_rooms;
Player* GameState::_player;
State GameState::_state;
std::vector<GameStateController*> GameState::_gameStates;
GameStateController* GameState::_currentState;

GameState::GameState()
{
}


GameState::~GameState()
{
	printf("GAME STATE DESTRUCTOR CALLED\n");

	if (_player)
		delete _player;

	/*if (_currentScene)
		delete _currentScene;
	*/

	for (auto& room : _rooms) 
		if (room)
			delete room;
	_rooms.clear();

	for (auto& gameState : _gameStates)
		if (gameState)
			delete gameState;
	_gameStates.clear();

	/*if (_currentState)
		delete _currentState;*/
}

void GameState::AddPlayer(Player* player)
{
	_player = player;
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
			_currentState = _gameStates[1];
		}
		break;

	case State::DIALOGUE:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			std::cout << "Regular State" << std::endl;
			_state = State::REGULAR;
			_currentState = _gameStates[0];
		}
		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			std::cout << "Regular State" << std::endl;
			_state = State::REGULAR;
			_currentState = _gameStates[0];
		}
		break;
	default:
		break;
	}
}

Player* GameState::GetPlayer()
{
	return _player;
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