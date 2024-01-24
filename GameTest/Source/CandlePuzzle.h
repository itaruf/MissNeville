#pragma once
#ifndef CANDLEPUZZLE_H_
#define CANDLEPUZZLE_H_

#include "Candle.h"
#include "Puzzle.h"

// Class which defines a puzzle involving candles
class CandlePuzzle : public Puzzle
{
protected:
	std::vector<Candle*> _candles;
public:
	Page* _page;
public:
	CandlePuzzle(Status status = Status::PENDING);
	~CandlePuzzle();

	std::vector<Candle*>& GetCandles();

	bool IsCleared() override;
};

#endif