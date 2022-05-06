#include "Room.h"

class GameState
{
private:
protected:
public:
	Room* currentRoom;
	std::vector<Room*> rooms;

	GameState(std::vector<Room*>& rooms) :  currentRoom{nullptr}
	{
		for each (auto var in rooms)
		{
			this->rooms.emplace_back(std::move(var));
		}
	}

	GameState(Room*& currentRoom, std::vector<Room*>& rooms) : currentRoom(std::move(currentRoom))
	{
		for each (auto var in rooms)
		{
			this->rooms.emplace_back(std::move(var));
		}
	}

	GameState(Room*& currentRoom) : currentRoom{ std::move(currentRoom) }
	{
	}

	~GameState()
	{
		delete currentRoom;

		for each (auto var in rooms)
		{
			delete var;
		}
	}
};

