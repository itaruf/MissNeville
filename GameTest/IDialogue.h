#pragma once
#ifndef IDIALOGUE_H_

#include <combaseapi.h>

interface IDialogue
{
public:
	virtual void PlayDialogue(int dialogueID) = 0;
	virtual void StopDialogue(int dialogueID) = 0;
};

#endif
