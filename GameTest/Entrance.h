#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "Scene.h"

#include "CandlePuzzle.h"
#include "Candle.h"
#include "GameState.h"
#include "TriggerScene.h";

//class Character;
////#include "Character.h"
#include "NPC.h"

class GameState;

// Entrance scene 
class Entrance : public Scene, std::enable_shared_from_this<Entrance>
{
private:
protected:
public:
	CandlePuzzle* _candlePuzzle;
	std::vector<Candle*> _candles;

	Entrance(int ID, std::vector<Actor*> actors, CandlePuzzle* candlePuzzle);
	Entrance(int ID, CandlePuzzle* candlePuzzle);
	~Entrance();

	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif