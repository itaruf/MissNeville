#pragma once
#ifndef TPPUZZLE_H_
#define TPPUZZLE_H_

#include "Puzzle.h"
#include "Candle.h"
#include "Page.h"

// Class which defines a puzzle involving candles
class TPPuzzle : public Puzzle
{
private:
protected:
public:
	Page* _page;
	TPPuzzle(Status status, Page* page);
	~TPPuzzle();

	bool IsCleared() override;
};

#endif
