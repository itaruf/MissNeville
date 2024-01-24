#include "../stdafx.h"
#include "Puzzle.h"

Puzzle::Puzzle(Status status) : _status{ status }
{
}

// Start the Puzzle 
bool Puzzle::StartPuzzle()
{
	// Can't start an already started or cleared puzzle
	if (_status == Status::PENDING || _status == Status::CLEARED)
		return false;
	_status = Status::PENDING;
	return true;
}

// End the puzzle
bool Puzzle::EndPuzzle()
{
	// Can't end an already not started or cleared puzzle
	if (_status == Status::NOTSTARTED || _status == Status::CLEARED)
		return false;
	_status = Status::CLEARED;
	return true;
}

// Get the current status of the puzzle
Status Puzzle::GetStatus()
{
	return _status;
}

void Puzzle::SetStatus(Status status)
{
	_status = status;
}