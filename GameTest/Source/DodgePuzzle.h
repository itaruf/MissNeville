#pragma once
#ifndef DODGEPUZZLE_H_
#define DODGEPUZZLE_H_

#include "Candle.h"
#include "Page.h"
#include "Puzzle.h"

// Class which defines a puzzle involving candles
class DodgePuzzle : public Puzzle
{
private:
	Page* _page;
public:
	DodgePuzzle(Status status = Status::PENDING, Page* page = nullptr);
	~DodgePuzzle() = default;

	Page* GetPage();
	void SetPage(Page* page);

	bool IsCleared() override;
};

#endif