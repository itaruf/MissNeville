#include "../stdafx.h"
#include "CandlePuzzle.h"

CandlePuzzle::CandlePuzzle(Status status) : Puzzle(status)
{
}

CandlePuzzle::~CandlePuzzle()
{
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
		auto page{ new Page(MPage.name + " 1", App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), Vector2D(512, 394), new Collision(16, 16), 0, DProps.p1) };
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