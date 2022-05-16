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
	Enigme* enigme;
public:
	Room(int ID, std::vector<Actor*> actors);
	Room(int ID, Actor* actor);
	Room(int ID);

	~Room() = default;

	Actor* GetActor(int index);
	const int& GetID() const;
	std::vector<Actor*>& GetActors();

	void AddActor(Actor* actor);

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual bool IsRoomCleared();
};

#endif