#include "stdafx.h"
#include "Puzzle.h"

Puzzle::Puzzle(Status status) : status{ status }
{
}

Puzzle::~Puzzle()
{
	printf("Puzzle DESTRUCTOR CALLED\n");
}

// Start the Puzzle 
bool Puzzle::StartPuzzle()
{
	// Can't start an already started or cleared puzzle
	if (status == Status::PENDING || status == Status::CLEARED)
		return false;
	status = Status::PENDING;
	return true;
}

// End the puzzle
bool Puzzle::EndPuzzle()
{
	// Can't end an already not started or cleared puzzle
	if (status == Status::NOTSTARTED || status == Status::CLEARED)
		return false;
	status = Status::CLEARED;
	return true;
}

// Get the current status of the puzzle
Puzzle::Status Puzzle::GetStatus()
{
	return status;
}