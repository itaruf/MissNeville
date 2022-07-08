#include "../stdafx.h"
#include "StateController.h"

Scene* StateController::_currentScene;
std::unordered_map<int, Scene*> StateController::_rooms;
Player* StateController::_player;
State StateController::_state;
std::vector<GameState*> StateController::_gameStates;
GameState* StateController::_currentGameState;
StateController::Delegate StateController::delegate;

StateController::StateController()
{
}


StateController::~StateController()
{
	printf("GAME STATE DESTRUCTOR CALLED\n");

	if (_player)
		delete _player;

	/*if (_currentScene)
		delete _currentScene;
	*/

	/*for (auto& state : _gameStates)
		if (state)
			delete state;
	_gameStates.clear();
	
	for (auto& room : _rooms)
		if (room)
			delete room;
	_rooms.clear();*/

	/*if (_currentGameState)
		delete _currentGameState;*/
}

void StateController::SetPlayer(Player* player)
{
	_player = player;
}

void StateController::SwitchState()
{
	/*delegate();*/

	switch (_state)
	{
	case State::REGULAR:
		// Start button to open the inventory / change the state back to INVENTORY
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START))
		{
			_currentGameState->Exit();
			// Updating state
			_currentGameState = _gameStates[1];
			_currentGameState->Enter();
			_state = State::INVENTORY;
		}
		break;

	case State::DIALOGUE:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
		{
			/*auto stateDialogue{ dynamic_cast<StateDialogue*>(_currentGameState) };

			if (!stateDialogue)
				break;

			if (stateDialogue->remainingDials < stateDialogue->maxLines)
				break;

			_currentGameState->Exit();
			_currentGameState = _gameStates[0];
			_currentGameState->Enter();
			_state = State::REGULAR;
		*/
		}
		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR //XINPUT_GAMEPAD_X  
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START) || App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		{
			_currentGameState->Exit();
			// Updating state
			_currentGameState = _gameStates[0];
			_currentGameState->Enter();
			_state = State::REGULAR;
		}
		break;
	default:
		break;
	}
}

Player* StateController::GetPlayer()
{
	return _player;
}

std::string StateController::PrintState()
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
