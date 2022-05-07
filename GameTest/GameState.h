#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Room.h"

class GameState
{
private:
protected:
public:
	int roomIndex{ 0 };
	Room* currentRoom{ nullptr };
	std::vector<Room*> rooms{ nullptr };

	GameState() = default;
	GameState(std::vector<Room*>& rooms);
	GameState(Room*& currentRoom, std::vector<Room*>& rooms);
	GameState(Room*& currentRoom);
	~GameState();
};

#endif