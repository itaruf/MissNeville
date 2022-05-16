#include "stdafx.h"
#include "GameState.h"

GameState::GameState(std::vector<Room*>& rooms) : currentRoom{ nullptr }
{
	for (auto room : rooms)
	{
		if (room)
			this->rooms.emplace_back(std::move(room));
	}
}

GameState::GameState(Room*& currentRoom, std::vector<Room*>& rooms) : currentRoom(std::move(currentRoom))
{
	for (auto room : rooms)
		this->rooms.emplace_back(std::move(room));
}

GameState::GameState(Room*& currentRoom) : currentRoom{ std::move(currentRoom) }
{
}

GameState::~GameState()
{
	if (currentRoom)
		delete currentRoom;

	if (player)
		delete player;

	for (auto room : rooms)
		if (room)
			delete room;
	rooms.clear();
}

void GameState::AddPlayer(Character* player)
{
	this->player = player;
}

Character* GameState::GetPlayer()
{
	return player;
}
