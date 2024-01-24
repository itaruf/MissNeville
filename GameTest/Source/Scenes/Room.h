#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include "../Actors/Characters/NPC.h"
#include "../Actors/Collectibles/MirrorShard.h"
#include "../Actors/Triggers/TriggerDialogue.h"
#include "../Scenes/Scene.h"
#include "../Systems/Puzzles/MirrorPuzzle.h"
#include "../Systems/States/StateController.h"

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