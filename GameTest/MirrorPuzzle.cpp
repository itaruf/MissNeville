#include "../stdafx.h"
#include "MirrorPuzzle.h"

MirrorPuzzle::MirrorPuzzle(Status status) : Puzzle(status), _mirror{nullptr}
{
}

MirrorPuzzle::~MirrorPuzzle()
{
}

bool MirrorPuzzle::IsCleared()
{
	if (_status == Status::CLEARED || _status == Status::NOTSTARTED)
		return true;

	return (_mirror->isRepaired());
}
