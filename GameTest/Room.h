#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include <algorithm>
#include <vector>
#include "Enigme.h"

class Actor;
class Character;
class Candle;

class Room
{
private:
protected:
	int ID;
	std::vector<Actor*> actors;
	std::vector<Candle*> candles;
	Character* player = nullptr;
	Enigme* enigme;
public:
	Room(int ID, std::vector<Actor*> actors);
	Room(int ID, Actor* actor);
	Room(int ID);

	~Room() = default;

	void AddActor(Actor* actor);
	Actor* GetActor(int index);
	const int& GetID() const;
	std::vector<Actor*>& GetActors();
	void AddPlayer(Character* player);
	Character* GetPlayer();
};

#endif