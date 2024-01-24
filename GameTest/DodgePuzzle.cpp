#include "../stdafx.h"
#include "DodgePuzzle.h"

DodgePuzzle::DodgePuzzle(Status status, Page* page) : Puzzle(status), _page{page}
{
}

Page* DodgePuzzle::GetPage()
{
	return _page;
}

void DodgePuzzle::SetPage(Page* page)
{
	_page = page;
	page = nullptr;
}

bool DodgePuzzle::IsCleared()
{
	if (_status == Status::CLEARED || _status == Status::NOTSTARTED)
		return true;

	return _page->isItemized();
}