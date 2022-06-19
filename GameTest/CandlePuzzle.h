#pragma once
#ifndef CANDLEPUZZLE_H_
#define CANDLEPUZZLE_H_

#include "Puzzle.h"
#include "Candle.h"

// Class which defines a puzzle involving candles
class CandlePuzzle : public Puzzle
{
private:
protected:
	std::vector<Candle*> _candles;
public:
	Page* _page;

	CandlePuzzle(Status status);
	~CandlePuzzle();

	std::vector<Candle*>& GetCandles();

	bool IsCleared() override;
};

#endif
