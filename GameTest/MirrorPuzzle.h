#pragma once
#ifndef MIRRORSHARDPUZZLE_H_
#define MIRRORSHARDPUZZLE_H_

#include "Puzzle.h"
#include "StateController.h"
class Mirror;
#include "Mirror.h"

class MirrorPuzzle : public Puzzle
{
private:
protected:
public:
	Mirror* _mirror;
	MirrorPuzzle(Status status = Status::PENDING);
	~MirrorPuzzle();
	bool IsCleared() override;
};

#endif

