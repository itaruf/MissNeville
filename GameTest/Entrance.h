#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "Candle.h"
#include "GameState.h"
#include "NPC.h"

class GameState;
// Entrance scene 
class Entrance : public Scene, std::enable_shared_from_this<Entrance>
{
private:
protected:
public:
	CandlePuzzle* candlePuzzle;
	std::vector<Candle*> candles;

	Entrance(int ID, std::vector<Actor*> actors, std::shared_ptr<GameState>& gameState, CandlePuzzle* candlePuzzle);
	Entrance(int ID, std::shared_ptr<GameState>& gameState, CandlePuzzle* candlePuzzle);
	~Entrance();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif