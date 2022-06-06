#include "stdafx.h"
#include "GameState.h"

Scene* GameState::currentScene;
std::vector<Scene*> GameState::rooms;
Player* GameState::player;
//std::vector<GameStateController*> gameStates;
//GameStateController* currentState;

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

Player* GameState::GetPlayer()
{
	return player;
}