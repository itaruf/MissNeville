#pragma once
#ifndef Puzzle_H_
#define Puzzle_H_

#include "EStatus.h"
#include "Utilities.h"

#include <vector>

// Base class to define the Puzzles of the game
class Puzzle
{
protected:
	Status _status;
public:
	// a puzzle has multiple states
	Delegate onSolved;
public:
	Puzzle(Status status = Status::PENDING);
	virtual ~Puzzle() = default;

	Status GetStatus();
	void SetStatus(Status status);

	bool StartPuzzle();
	bool EndPuzzle();

	virtual bool IsCleared() = 0;
};

#endif