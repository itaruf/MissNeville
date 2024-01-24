#pragma once
#ifndef MIRRORSHARDPUZZLE_H_
#define MIRRORSHARDPUZZLE_H_

#include "Mirror.h"
#include "Puzzle.h"
#include "StateController.h"

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