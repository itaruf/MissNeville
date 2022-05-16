#include "stdafx.h"
#include "Enigme.h"

Enigme::Enigme(Status status) : status{ status }
{
}

Enigme::~Enigme()
{
}

bool Enigme::IsCleared()
{
	return false;
}

bool Enigme::StartEnigme()
{
	if (status == Status::PENDING || status == Status::CLEARED)
		return false;
	status = Status::PENDING;
	return true;
}

bool Enigme::EndEnigme()
{
	if (status == Status::NOTSTARTED || status == Status::CLEARED)
		return false;
	status = Status::CLEARED;
	return true;
}

Enigme::Status Enigme::GetStatus()
{
	return status;
}