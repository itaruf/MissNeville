#include "../stdafx.h"
#include "DodgePuzzle.h"

DodgePuzzle::DodgePuzzle(Status status, Page* page) : Puzzle(status), _page{page}
{
}

DodgePuzzle::~DodgePuzzle()
{
}

bool DodgePuzzle::IsCleared()
{
	if (_status == Status::CLEARED || _status == Status::NOTSTARTED)
		return true;

	return _page->itemized;
}
