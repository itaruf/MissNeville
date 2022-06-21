#pragma once
#ifndef HALL_H_
#define HALL_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "TriggerScene.h";
//class Character;
#include "Character.h"
#include "NPC.h"

class StateMain;
// Hall scene 
class Hall : public Scene, std::enable_shared_from_this<Hall>
{
private:
protected:
public:
	CandlePuzzle* _candlePuzzle;
	std::vector<Candle*> _candles;

	Hall(int ID, std::vector<Actor*> actors, CandlePuzzle* candlePuzzle);
	Hall(int ID, CandlePuzzle* candlePuzzle);
	~Hall();

	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
	void OnMirrorShattered() override;
};

#endif