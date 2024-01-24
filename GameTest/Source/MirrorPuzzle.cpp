#include "../stdafx.h"
#include "MirrorPuzzle.h"

MirrorPuzzle::MirrorPuzzle(Status status) : Puzzle(status), _mirror{nullptr}
{
}

void MirrorPuzzle::SetMirror(Mirror* mirror)
{
	_mirror = mirror;
	mirror = nullptr;
}

bool MirrorPuzzle::IsCleared()
{
	if (_status == Status::CLEARED || _status == Status::NOTSTARTED)
		return true;

	return (_mirror->isRepaired());
}