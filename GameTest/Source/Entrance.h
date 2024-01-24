#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "Dialogues.h"
#include "StateController.h"
#include "Scene.h"
#include "NPC.h"
#include "Room.h"

#include "Candle.h"
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