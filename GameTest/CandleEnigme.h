#pragma once
#ifndef CANDLEENIGME_H_
#define CANDLEENIGME_H_

#include "Enigme.h"
#include "Candle.h"

class CandleEnigme : public Enigme
{
private:
protected:
	std::vector<Candle*> candles;
public:
	CandleEnigme(Status status);
	~CandleEnigme() = default;

	std::vector<Candle*>& GetCandles();

	bool IsCleared() override;
};

#endif
