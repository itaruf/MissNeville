#include "stdafx.h"
#include "Room.h"

Room::Room(int ID, std::vector<Actor*> actors, std::shared_ptr<GameState> gameState) : ID{ ID }, actors{ actors }, gameState{ gameState } {}

Room::Room(int ID, Actor* actor, std::shared_ptr<GameState> gameState) : ID{ ID }, gameState{ gameState }
{ 
	actors.emplace_back(actor); 
}

Room::Room(int ID, std::shared_ptr<GameState> gameState) : ID{ ID }, gameState{ gameState } {}

Room::~Room()
{
	for (auto actor : actors)
		if (actor)
			delete actor;
	actors.clear();
}

void Room::AddActor(Actor* actor)
{
	actors.emplace_back(actor);
}

Actor* Room::GetActor(int index)
{
	return actors[index];
}

const int& Room::GetID() const
{
	return ID;
}

std::vector<Actor*>& Room::GetActors()
{
	return actors;
}


void Room::Init()
{
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

bool Room::RemoveActor(Actor* actor)
{
	if (!actor)
		return false;

	auto it = std::find(actors.begin(), actors.end(), actor);

	if (it != actors.end())
	{
		actors.erase(it);
		actor = nullptr;
		delete actor;
		return true;
	}
	return false;
}
