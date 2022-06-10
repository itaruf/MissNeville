#pragma once
#ifndef LOUNGE_H_
#define LOUNGE_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "Candle.h"
#include "GameState.h"
#include "NPC.h"

class GameState;
// Lounge scene 
class Lounge : public Scene, std::enable_shared_from_this<Lounge>
{
private:
protected:
public:
	Lounge(int ID, std::vector<Actor*> actors);
	Lounge(int ID);
	~Lounge();

	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif