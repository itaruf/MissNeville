#include "stdafx.h"
#include "CandleEnigme.h"

CandleEnigme::CandleEnigme(Status status) : Enigme(status)
{
}

bool CandleEnigme::IsCleared()
{
	if (status == Status::CLEARED || status == Status::NOTSTARTED)
		return true;

	for each (const auto& candle in candles)
	{
		if (!candle->isEnlighted())
			return false;
	}
	return EndEnigme();
}

std::vector<Candle*>& CandleEnigme::GetCandles()
{
	return candles;
}
