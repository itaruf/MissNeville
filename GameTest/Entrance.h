#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "Room.h"
#include "CandleEnigme.h"
#include "Candle.h"
#include "GameState.h"

class GameState;
class Entrance : public Room, std::enable_shared_from_this<Entrance>
{
private:
	/*enum class Status
	{
		NOTSTARTED,
		PENDING,
		CLEARED,
	};*/

protected:
public:
	CandleEnigme* candleEnigme;
	std::vector<Candle*> candles;

	Entrance(int ID, std::vector<Actor*> actors, std::shared_ptr<GameState> gameState, CandleEnigme* candleEnigme);
	Entrance(int ID, Actor* actor, std::shared_ptr<GameState> gameState, CandleEnigme* candleEnigme);
	Entrance(int ID, std::shared_ptr<GameState> gameState, CandleEnigme* candleEnigme);
	~Entrance();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif