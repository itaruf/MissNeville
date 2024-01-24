#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "../Scenes/Scene.h"
#include "../Systems/Dialogues/Dialogues.h"
#include "../Systems/States/StateController.h"

#include "Room.h"

#include "../Actors/Characters/NPC.h"
#include "../Actors/Candles/Candle.h"

// Entrance scene 
class Entrance : public Scene
{
public:
	Entrance(int ID);
	~Entrance() = default;

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;

	bool IsRoomCleared() override;

	void Intro();
	void Outro();
};

#endif