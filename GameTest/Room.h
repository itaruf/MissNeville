#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include "Scene.h"
#include "MirrorPuzzle.h"
#include "StateController.h"
#include "NPC.h"
#include "MirrorShard.h"
#include "TriggerDialogue.h"

class StateController;
// Room scene 
class Room : public Scene
{
private:
protected:
public:
	MirrorPuzzle* _mirrorPuzzle;

	Room(int ID);
	Room(int ID, MirrorPuzzle*);

	~Room();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
	void OnMirrorShattered();
};

#endif