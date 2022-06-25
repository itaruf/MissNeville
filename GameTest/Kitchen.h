#pragma once
#ifndef KITCHEN_H_
#define KITCHEN_H_

#include "Scene.h"
#include "StateMain.h"
#include "NPC.h"
#include "DodgePuzzle.h"
#include "Button.h"
#include "MirrorShard.h"

class StateMain;
// Kitchen scene 
class Kitchen : public Scene
{
private:
protected:
public:
	DodgePuzzle* _dodgePuzzle;
	std::vector<Button*> _buttons;
	Delegate _onCanOpenCell;
	Kitchen(int ID);
	Kitchen(int ID, DodgePuzzle*);

	~Kitchen();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
	bool CanOpenCell();
};

#endif