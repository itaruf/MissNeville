#pragma once
#ifndef Puzzle_H_
#define Puzzle_H_

#include <vector>

// Base class to define the Puzzles of the game
class Puzzle
{
private:
protected:
public:

	// a puzzle has multiple states
	enum class Status
	{
		NOTSTARTED,
		PENDING,
		CLEARED,
	};

	Status _status;

	Puzzle(Status status);
	virtual ~Puzzle();

	Status GetStatus();
	virtual bool IsCleared() = 0;
	bool StartPuzzle();
	bool EndPuzzle();
};

#endif