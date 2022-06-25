#pragma once
#ifndef Puzzle_H_
#define Puzzle_H_

#include <vector>
#include "Utilities.h"
#include "EStatus.h"

// Base class to define the Puzzles of the game
class Puzzle
{
private:
protected:
public:

	// a puzzle has multiple states
	Status _status;
	Delegate _onSolved;

	Puzzle(Status status = Status::PENDING);
	virtual ~Puzzle();

	Status GetStatus();
	virtual bool IsCleared() = 0;
	bool StartPuzzle();
	bool EndPuzzle();
};

#endif