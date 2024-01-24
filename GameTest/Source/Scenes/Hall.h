#pragma once
#ifndef HALL_H_
#define HALL_H_

#include "../Actors/Characters/Character.h"
#include "../Actors/Characters/NPC.h"
#include "../Actors/Triggers/TriggerScene.h";
#include "../Systems/Puzzles/CandlePuzzle.h"

#include "Scene.h"

// Hall scene 
class Hall : public Scene, std::enable_shared_from_this<Hall>
{
private:
	CandlePuzzle* _candlePuzzle;
	std::vector<Candle*> _candles;
public:
	Hall(int ID);
	Hall(int ID, CandlePuzzle*);

	~Hall();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;

	bool IsRoomCleared() override;
};

#endif