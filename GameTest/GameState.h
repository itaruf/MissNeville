#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Room.h"
#include "Entrance.h"
#include "Player.h"

class Room;
class Entrance;
class Player;

class GameState
{
private:
protected:
public:
	int roomIndex{ 0 };
	Room* currentRoom;
	std::vector<Room*> rooms;
	Player* player{ nullptr };

	GameState();
	GameState(std::vector<Room*>& rooms);
	GameState(Room* currentRoom, std::vector<Room*>& rooms);
	GameState(Room* currentRoom);
	~GameState();

	Player* GetPlayer();

	void AddPlayer(Player* player);
};

#endif