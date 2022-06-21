#include "../stdafx.h"
#include "StateMain.h"

Scene* StateMain::_currentScene;
std::unordered_map<int, Scene*> StateMain::_rooms;
Player* StateMain::_player;
State StateMain::_state;
std::vector<StateController*> StateMain::_stateControllers;
StateController* StateMain::_currentStateController;
StateMain::Delegate StateMain::delegate;

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

	/*for (auto& state : _stateControllers)
		if (state)
			delete state;
	_stateControllers.clear();
	
	for (auto& room : _rooms)
		if (room)
			delete room;
	_rooms.clear();*/

	/*if (_currentStateController)
		delete _currentStateController;*/
}

void StateMain::AddPlayer(Player* player)
{
	_player = player;
}

void StateMain::SwitchState()
{
	/*delegate();*/

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
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
		{
			/*auto stateDialogue{ dynamic_cast<StateDialogue*>(_currentStateController) };

			if (!stateDialogue)
				break;

			if (stateDialogue->remainingDials < stateDialogue->maxLines)
				break;

			_currentStateController->Exit();
			_currentStateController = _stateControllers[0];
			_currentStateController->Enter();
			_state = State::REGULAR;
		*/
		}
		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START) || App::GetController().CheckButton(XINPUT_GAMEPAD_B))
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
