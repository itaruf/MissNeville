#include "../stdafx.h"
#include "Room.h"

Room::Room(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Room::Room(int ID) : Scene(ID)
{
}

Room::~Room()
{
}

bool Room::Init()
{
	if (Scene::Init())
		return true;

	return false;
}

void Room::Update(float deltaTime)
{
}

void Room::Render()
{
}

bool Room::IsRoomCleared()
{
	return false;
}
