#pragma once
#ifndef MIRRORSHARDPUZZLE_H_
#define MIRRORSHARDPUZZLE_H_

#include "../../Actors/Mirrors/Mirror.h"
#include "../../Systems/Puzzles/Puzzle.h"
#include "../../Systems/States/StateController.h"

class Mirror;

class MirrorPuzzle : public Puzzle
{
private:
	Mirror* _mirror;
public:
	MirrorPuzzle(Status status = Status::PENDING);
	~MirrorPuzzle() = default;

	void SetMirror(Mirror* mirror);

	bool IsCleared() override;
};

#endif