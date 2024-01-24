#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include "../Systems/Puzzles/MirrorPuzzle.h"
#include "../Actors/Collectibles/MirrorShard.h"
#include "../Actors/Characters/NPC.h"
#include "../Scenes/Scene.h"
#include "../Systems/States/StateController.h"
#include "../Actors/Triggers/TriggerDialogue.h"

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