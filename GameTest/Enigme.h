#pragma once
#ifndef ENIGME_H_
#define ENIGME_H_

class Enigme
{
private:
protected:
	enum class Status
	{
		NOTSTARTED,
		PENDING,
		CLEARED,
	};
	Status status;
public:
	Enigme(Status status);
	virtual bool IsCleared();
	bool StartEnigme();
	bool EndEnigme();
	Status GetStatus();
	virtual ~Enigme() = default;
};

#endif