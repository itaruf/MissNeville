#pragma once
#ifndef LOUNGE_H_
#define LOUNGE_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "Candle.h"
#include "StateMain.h"
#include "NPC.h"

class StateMain;
// Lounge scene 
class Lounge : public Scene, std::enable_shared_from_this<Lounge>
{
private:
protected:
public:
	Lounge(int ID);
	~Lounge();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
};

#endif