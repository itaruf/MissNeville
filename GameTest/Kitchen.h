#pragma once
#ifndef KITCHEN_H_
#define KITCHEN_H_

#include "Button.h"
#include "DodgePuzzle.h"
#include "MirrorShard.h"
#include "NPC.h"
#include "Scene.h"
#include "StateController.h"

// Kitchen scene 
class Kitchen : public Scene
{
private:
	DodgePuzzle* _dodgePuzzle;
	std::vector<Button*> _buttons;
	Delegate onOpenCell;
public:
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