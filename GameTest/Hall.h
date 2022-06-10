#pragma once
#ifndef HALL_H_
#define HALL_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "Candle.h"
#include "GameState.h"
#include "NPC.h"

class GameState;
// Hall scene 
class Hall : public Scene, std::enable_shared_from_this<Hall>
{
private:
protected:
public:
	Hall(int ID, std::vector<Actor*> actors);
	Hall(int ID);
	~Hall();

	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif