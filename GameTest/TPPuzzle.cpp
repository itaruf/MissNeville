#include "../stdafx.h"
#include "TPPuzzle.h"

TPPuzzle::TPPuzzle(Status status, Page* page) : Puzzle(status), _page{page}
{
}

bool TPPuzzle::IsCleared()
{
	if (_status == Status::CLEARED || _status == Status::NOTSTARTED)
		return true;

	return _page->isItemized();
}