#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include <algorithm>
#include <vector>
#include "Enigme.h"
class Actor;
#include "Actor.h"

class GameState;
class Character;
class Candle;

class Room
{
private:
protected:
	int ID;
	std::vector<Actor*> actors;
	std::shared_ptr<GameState> gameState;
public:
	Room(int ID, std::vector<Actor*> actors, std::shared_ptr<GameState> gameState);
	Room(int ID, Actor* actor, std::shared_ptr<GameState> gameState);
	Room(int ID, std::shared_ptr<GameState> gameState);

	virtual ~Room();

	Actor* GetActor(int index);
	const int& GetID() const;
	std::vector<Actor*>& GetActors();
	bool RemoveActor(Actor* item);
	void AddActor(Actor* actor);

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual bool IsRoomCleared();
};

#endif