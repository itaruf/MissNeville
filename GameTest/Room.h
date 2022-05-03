#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include <algorithm>
#include <vector>

class Actor;
class Room
{
private:
protected:
	int ID;
	std::vector<Actor*> actors;
public:
	Room(int ID, std::vector<Actor*>& actors);
	Room(int ID, Actor*& actor);
	Room(int ID);

	~Room() = default;

	void AddActor(Actor* actor);
	Actor*& GetActor(int index);
	int& GetID();
	std::vector<Actor*>& GetActors();
};

#endif