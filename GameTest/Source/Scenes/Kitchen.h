#pragma once
#ifndef KITCHEN_H_
#define KITCHEN_H_

#include "../Actors/Buttons/Button.h"
#include "../Actors/Characters/NPC.h"
#include "../Actors/Collectibles/MirrorShard.h"
#include "../Systems/Puzzles/DodgePuzzle.h"
#include "../Systems/States/StateController.h"

#include "Scene.h"

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