#pragma once
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "Scene.h"
#include "TPPuzzle.h"
#include "StateController.h"
#include "NPC.h"
#include "StateDialogue.h"
#include "MirrorShard.h"

class StateController;
// Library scene 
class Library : public Scene
{
private:
protected:
public:
	TPPuzzle* _TPPuzzle;
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