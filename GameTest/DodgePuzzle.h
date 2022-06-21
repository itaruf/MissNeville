#pragma once
#ifndef DODGEPUZZLE_H_
#define DODGEPUZZLE_H_

#include "Puzzle.h"
#include "Candle.h"
#include "Page.h"

// Class which defines a puzzle involving candles
class DodgePuzzle : public Puzzle
{
private:
protected:
public:
	Page* _page;
	DodgePuzzle(Status status, Page* page);
	~DodgePuzzle();

	bool IsCleared() override;
};

#endif
