#pragma once
#ifndef ENIGME_H_
#define ENIGME_H_

#include <vector>

class Enigme
{
private:
protected:
public:
	enum class Status
	{
		NOTSTARTED,
		PENDING,
		CLEARED,
	};
	Status status;

	Enigme(Status status);
	virtual ~Enigme() = default;

	Status GetStatus();
	virtual bool IsCleared();

	bool StartEnigme();
	bool EndEnigme();
};

#endif