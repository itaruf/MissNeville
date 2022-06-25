#pragma once
#ifndef LOUNGE_H_
#define LOUNGE_H_

#include "Scene.h"
#include "StateMain.h"
#include "NPC.h"
#include "DodgePuzzle.h"
#include "Button.h"
#include "MirrorShard.h"

class StateMain;
// Lounge scene 
class Lounge : public Scene
{
private:
protected:
public:
	DodgePuzzle* _dodgePuzzle;
	std::vector<Button*> _buttons;
	Delegate _onCanOpenCell;
	Lounge(int ID);
	Lounge(int ID, DodgePuzzle*);

	~Lounge();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
	bool CanOpenCell();
};

#endif