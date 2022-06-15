#include "../stdafx.h"
#include "StateMain.h"

Scene* StateMain::_currentScene;
std::vector<Scene*> StateMain::_rooms;
Player* StateMain::_player;
State StateMain::_state;
std::vector<StateController*> StateMain::_stateControllers;
StateController* StateMain::_currentStateController;

StateMain::StateMain()
{
}


StateMain::~StateMain()
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

	for (auto& state : _stateControllers)
		if (state)
			delete state;
	_stateControllers.clear();

	/*if (_currentStateController)
		delete _currentStateController;*/
}

void StateMain::AddPlayer(Player* player)
{
	_player = player;
}

using namespace std::chrono;

void StateMain::OnChangeState()
{
	_currentStateController = _stateControllers[0];
	std::cout << PrintState() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void StateMain::SwitchState()
{
	switch (_state)
	{
	case State::REGULAR:
		// Start button to open the inventory / change the state back to INVENTORY
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START))
		{
			_currentStateController->Exit();
			// Updating state
			_currentStateController = _stateControllers[1];
			_currentStateController->Enter();
			_state = State::INVENTORY;
		}
		break;

	case State::DIALOGUE:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		{
			/*std::cout << "CLOSING" << std::endl;*/
			_currentStateController->Exit();
			_currentStateController = _stateControllers[0];
			_currentStateController->Enter();
			_state = State::REGULAR;
			// Updating state


			//using namespace std::chrono_literals;
			//std::cout << "Hello waiter\n" << std::flush;
			//auto start = std::chrono::high_resolution_clock::now();
			//std::this_thread::sleep_for(1000ms);
			//auto end = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<double, std::milli> elapsed = end - start;
			//std::cout << "Waited " << elapsed.count() << " ms\n";

			//std::future<void> fut = std::async(std::launch::async, &StateMain::OnChangeState, this);

			//if (fut.wait_for(1000ms) == std::future_status::ready) {
			//	// Result is ready.
			//	std::cout << PrintState() << std::endl;
			//	_state = State::REGULAR;
			//	_currentStateController->Enter();
			//}
			//else {
			//	// Do something else.
			//	break;
			//}

			/*fut.wait();*/
			/*fut.get();*/

			/*_currentStateController = _stateControllers[0];
			_currentStateController->Enter();*/

		}
		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
		{
			_currentStateController->Exit();
			// Updating state
			_currentStateController = _stateControllers[0];
			_currentStateController->Enter();
			_state = State::REGULAR;
		}
		break;
	default:
		break;
	}
}

Player* StateMain::GetPlayer()
{
	return _player;
}

std::string StateMain::PrintState()
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
