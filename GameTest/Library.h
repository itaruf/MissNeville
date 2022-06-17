#pragma once
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "Scene.h"
#include "CandlePuzzle.h"
#include "Candle.h"
#include "StateMain.h"
#include "NPC.h"

class StateMain;
// Library scene 
class Library : public Scene, std::enable_shared_from_this<Library>
{
private:
protected:
public:
	Vector2D* startingPos{ nullptr };
	Library(int ID, std::vector<Actor*> actors);
	Library(int ID);
	~Library();

	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	bool IsRoomCleared() override;
};

#endif