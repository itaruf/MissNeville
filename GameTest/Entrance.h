#pragma once
#ifndef HALL_H_
#define HALL_H_

#include "Scene.h"
#include "MirrorPuzzle.h"
#include "Candle.h"
#include "StateMain.h"
#include "NPC.h"
#include "MirrorShard.h"

class StateMain;
// Entrance scene 
class Entrance : public Scene, std::enable_shared_from_this<Entrance>
{
private:
protected:
public:
	MirrorPuzzle* _mirrorPuzzle;
	Entrance(int ID, std::vector<Actor*> actors);
	Entrance(int ID);
	~Entrance();

	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif