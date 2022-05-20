#include "stdafx.h"
#include "GameState.h"

GameState::GameState(std::vector<Room*>& rooms) : currentRoom{ nullptr }
{
	for (auto& room : rooms)
	{
		if (room)
			this->rooms.emplace_back(std::move(room));
	}
}

GameState::GameState(Room* currentRoom, std::vector<Room*>& rooms) : currentRoom(std::move(currentRoom))
{
	for (auto& room : rooms)
	{
		if (room)
			this->rooms.emplace_back(std::move(room));
	}
}

GameState::GameState(Room* currentRoom) : currentRoom{ std::move(currentRoom) }
{
}


GameState::GameState() : currentRoom{ nullptr }
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

	/*if (currentRoom)
	{
		delete currentRoom;
		currentRoom = nullptr;
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

void GameState::AddPlayer(Character* player)
{
	this->player = player;
	player = nullptr;
}

Character* GameState::GetPlayer()
{
	return player;
}
