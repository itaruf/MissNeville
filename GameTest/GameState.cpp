#include "../stdafx.h"
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

using namespace std::chrono;

void GameState::OnChangeState()
{
	_currentState = _gameStates[0];
	std::cout << PrintState() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void GameState::SwitchState()
{
	switch (_state)
	{
	case State::REGULAR:
		// Start button to open the inventory / change the state back to INVENTORY
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START))
		{
			_currentState->Exit();
			// Updating state
			_currentState = _gameStates[1];
			_currentState->Enter();
			_state = State::INVENTORY;
		}
		break;

	case State::DIALOGUE:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		{
			/*std::cout << "CLOSING" << std::endl;*/
			_currentState->Exit();
			_currentState = _gameStates[0];
			_currentState->Enter();
			_state = State::REGULAR;
			// Updating state


			//using namespace std::chrono_literals;
			//std::cout << "Hello waiter\n" << std::flush;
			//auto start = std::chrono::high_resolution_clock::now();
			//std::this_thread::sleep_for(1000ms);
			//auto end = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<double, std::milli> elapsed = end - start;
			//std::cout << "Waited " << elapsed.count() << " ms\n";

			//std::future<void> fut = std::async(std::launch::async, &GameState::OnChangeState, this);

			//if (fut.wait_for(1000ms) == std::future_status::ready) {
			//	// Result is ready.
			//	std::cout << PrintState() << std::endl;
			//	_state = State::REGULAR;
			//	_currentState->Enter();
			//}
			//else {
			//	// Do something else.
			//	break;
			//}

			/*fut.wait();*/
			/*fut.get();*/

			/*_currentState = _gameStates[0];
			_currentState->Enter();*/

		}
		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		{
			_currentState->Exit();
			// Updating state
			_currentState = _gameStates[0];
			_currentState->Enter();
			_state = State::REGULAR;
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
