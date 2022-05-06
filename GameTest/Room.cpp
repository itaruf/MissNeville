#include "stdafx.h"
#include "Room.h"

Room::Room(int ID, std::vector<Actor*> actors) : ID{ ID }, actors{ actors } {}

Room::Room(int ID, Actor* actor) : ID{ ID } { actors.emplace_back(actor); }

Room::Room(int ID) : ID{ ID } {}

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

void Room::AddPlayer(Character* player)
{
	this->player = player;
}

Character* Room::GetPlayer()
{
	return player;
}
