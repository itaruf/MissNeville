#include "stdafx.h"
#include "CandlePuzzle.h"

CandlePuzzle::CandlePuzzle(Status status) : Puzzle(status)
{
}

CandlePuzzle::~CandlePuzzle()
{
	printf("CANDLE Puzzle DESTRUCTOR CALLED\n");

	/*for (auto& candle : candles)
	{
		if (candle)
			delete candle;
	}*/
	candles.clear();
}

// Check if the candle puzzle is cleared
bool CandlePuzzle::IsCleared()
{
	if (status == Status::CLEARED || status == Status::NOTSTARTED)
		return true;

	// The condition for success is lightening all the involved candles
	for (const auto& candle : candles)
	{
		if (!candle->isEnlighted())
			return false;
	}
	/*return EndPuzzle();*/
	return true;
}

// Get the involved candles of the puzzle
std::vector<Candle*>& CandlePuzzle::GetCandles()
{
	return candles;
}
