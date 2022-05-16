#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Room.h"
#include "Entrance.h"
#include "Character.h"

class Room;
class Entrance;
class Character;

class GameState
{
private:
protected:
public:
	int roomIndex{ 0 };
	Room* currentRoom{ nullptr };
	std::vector<Room*> rooms{ nullptr };
	Entrance* entrance{ nullptr };
	Character* player{ nullptr };

	GameState() = default;
	GameState(std::vector<Room*>& rooms);
	GameState(Room*& currentRoom, std::vector<Room*>& rooms);
	GameState(Room*& currentRoom);
	~GameState();

	Character* GetPlayer();

	void AddPlayer(Character* player);
};

#endif