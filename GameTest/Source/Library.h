#pragma once
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "MirrorShard.h"
#include "NPC.h"
#include "Scene.h"
#include "StateController.h"
#include "StateDialogue.h"
#include "TPPuzzle.h"

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