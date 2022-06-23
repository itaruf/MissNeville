#include "../stdafx.h"
#include "CandlePuzzle.h"

CandlePuzzle::CandlePuzzle(Status status) : Puzzle(status)
{
}

CandlePuzzle::~CandlePuzzle()
{
	printf("CANDLE Puzzle DESTRUCTOR CALLED\n");

	/*for (auto& candle : _candles)
	{
		if (candle)
			delete candle;
	}*/
	_candles.clear();
}

// Check if the candle puzzle is cleared
bool CandlePuzzle::IsCleared()
{
	if (_status == Status::CLEARED || _status == Status::NOTSTARTED)
		return true;

	// The condition for success is lightening all the involved candles
	for (const auto& candle : _candles)
	{
		if (!candle->isEnlighted())
			return false;
	}

	if (!_page)
	{
		std::string description{ "\n[Page 1] :\n\nDear diary,\nToday's the same day as always.\nOur governess, Ms. Smith, scolded me all day for not behaving like a \"proper english lady\" or so she says..\nIt is always : \"Charlotte ! do not do this !\" or \"No.. Charlotte ! do not say this, say that instead !\", it is so frustrating !\nBut why is Edward bypassing everything when he behaves like a pig !? It is so unfair..\nWell, as we say : \"Birds of a feather flock together\" hehe !\nOh ! Ms. Pig better not read this or she is going to grunt with her pig nose wiiiiide open hehe !\nBlessed be the day she finally leaves our house !\n\n- Charlotte Neville." };

		auto page{ new Page(MPage.name + " 1", App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(512, 394), new Collision(16, 16), 0, description) };

		_page = page;
	}

	/*return EndPuzzle();*/
	return true;
}

// Get the involved candles of the puzzle
std::vector<Candle*>& CandlePuzzle::GetCandles()
{
	return _candles;
}
