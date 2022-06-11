#pragma once
#ifndef MIRRORSHARDPUZZLE_H_
#define MIRRORSHARDPUZZLE_H_

#include "Puzzle.h"
#include "GameState.h"
class Mirror;
#include "Mirror.h"

class MirrorPuzzle : public Puzzle
{
private:
protected:
public:
	Mirror* _mirror;
	MirrorPuzzle(Status status);
	~MirrorPuzzle();
	bool IsCleared() override;
};

#endif

