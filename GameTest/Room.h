#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "Candle.h"
#include "GameState.h"
#include "NPC.h"

class GameState;
// Room scene 
class Room : public Scene, std::enable_shared_from_this<Room>
{
private:
protected:
public:
	Room(int ID, std::vector<Actor*> actors);
	Room(int ID);
	~Room();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif