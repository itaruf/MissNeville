#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "Room.h"
#include "CandleEnigme.h"
#include "Candle.h"
#include "GameState.h"

class GameState;
class Entrance : public Room
{
private:
protected:
public:
	GameState* gameState;
	CandleEnigme* candleEnigme;
	std::vector<Candle*> candles;
	Entrance(int ID, std::vector<Actor*> actors, CandleEnigme* candleEnigme);
	Entrance(int ID, Actor* actor, CandleEnigme* candleEnigme);
	Entrance(int ID, CandleEnigme* candleEnigme);
	~Entrance() = default;
	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
};

#endif