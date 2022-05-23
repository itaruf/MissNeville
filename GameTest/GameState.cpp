#include "stdafx.h"
#include "GameState.h"

GameState::GameState(std::vector<Scene*>& rooms) : currentScene{ nullptr }
{
	for (auto& room : rooms)
	{
		if (room)
			this->rooms.emplace_back(std::move(room));
	}
}

GameState::GameState(Scene* currentScene, std::vector<Scene*>& rooms) : currentScene(std::move(currentScene))
{
	for (auto& room : rooms)
	{
		if (room)
			this->rooms.emplace_back(std::move(room));
	}
}

GameState::GameState(Scene* currentScene) : currentScene{ std::move(currentScene) }
{
}


GameState::GameState() : currentScene{ nullptr }
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