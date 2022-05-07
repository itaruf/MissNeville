#include "stdafx.h"
#include "GameState.h"

GameState::GameState(std::vector<Room*>& rooms) : currentRoom{ nullptr }
{
	for each (auto var in rooms)
	{
		this->rooms.emplace_back(std::move(var));
	}
}

GameState::GameState(Room*& currentRoom, std::vector<Room*>& rooms) : currentRoom(std::move(currentRoom))
{
	for each (auto var in rooms)
	{
		this->rooms.emplace_back(std::move(var));
	}
}

GameState::GameState(Room*& currentRoom) : currentRoom{ std::move(currentRoom) }
{
}

GameState::~GameState()
{
	delete currentRoom;
	for each (auto var in rooms)
		delete var;
	
}