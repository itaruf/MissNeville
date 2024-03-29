#pragma once
#ifndef TPPUZZLE_H_
#define TPPUZZLE_H_

#include "../../Actors/Candles/Candle.h"
#include "../../Actors/Collectibles/Page.h"

#include "Puzzle.h"

// Class which defines a puzzle involving candles
class TPPuzzle : public Puzzle
{
public:
	Page* _page;
public:
	TPPuzzle(Status status = Status::PENDING, Page* page = nullptr);
	~TPPuzzle() = default;

	bool IsCleared() override;
};

#endif