#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include "MirrorPuzzle.h"
#include "MirrorShard.h"
#include "NPC.h"
#include "Scene.h"
#include "StateController.h"
#include "TriggerDialogue.h"

// Room scene 
class Room : public Scene
{
public:
	MirrorPuzzle* _mirrorPuzzle;
public:
	Room(int ID);
	Room(int ID, MirrorPuzzle*);

	~Room() = default;

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;

	bool IsRoomCleared() override;

	void OnMirrorShattered();
};

#endif