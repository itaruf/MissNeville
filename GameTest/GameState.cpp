#include "stdafx.h"
#include "GameState.h"

Scene* GameState::currentScene;
std::vector<Scene*> GameState::rooms;
Player* GameState::player;
State GameState::state;
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

	/*if (currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
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
	switch (state)
	{
	case State::REGULAR:
		// Start button to open the inventory / change the state back to INVENTORY
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			std::cout << "Inventory State" << std::endl;
			state = State::INVENTORY;
			currentState = gameStates[1];
		}
		break;

	case State::DIALOGUE:

		break;

	case State::INVENTORY:
		// Face button Right to close the inventory / change the state back to REGULAR
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			std::cout << "Regular State" << std::endl;
			state = State::REGULAR;
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
	switch (state)
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