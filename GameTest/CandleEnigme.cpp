#include "stdafx.h"
#include "CandleEnigme.h"

CandleEnigme::CandleEnigme(Status status) : Enigme(status)
{
}

CandleEnigme::~CandleEnigme()
{
	for (auto candle : candles)
		if (candle)
			delete candle;
	candles.clear();
}

bool CandleEnigme::IsCleared()
{
	if (status == Status::CLEARED || status == Status::NOTSTARTED)
		return true;

	for (const auto candle : candles)
	{
		if (!candle->isEnlighted())
			return false;
	}
	/*return EndEnigme();*/
	return true;
}

std::vector<Candle*>& CandleEnigme::GetCandles()
{
	return candles;
}
