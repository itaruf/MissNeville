#pragma once
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "../Actors/Characters/NPC.h"
#include "../Actors/Collectibles/MirrorShard.h"
#include "../Systems/States/StateController.h"
#include "../Systems/States/StateDialogue.h"
#include "../Systems/Puzzles/TPPuzzle.h"

#include "Scene.h"

// Library scene 
class Library : public Scene
{
private:
	TPPuzzle* _TPPuzzle;
public:
	Library(int ID);
	Library(int ID, TPPuzzle*);
	~Library();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
};

#endif