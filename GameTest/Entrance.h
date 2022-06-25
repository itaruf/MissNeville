#pragma once
#ifndef ENTRANCE_H_
#define ENTRANCE_H_

#include "Scene.h"
#include "StateMain.h"
#include "NPC.h"
#include "Dialogues.h"
#include "Candle.h"
#include "Room.h"

class StateMain;
// Entrance scene 
class Entrance : public Scene
{
private:
protected:
public:
	Entrance(int ID);
	~Entrance();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
	void Intro();
	void Outro();
};

#endif