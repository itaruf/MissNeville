#pragma once
#ifndef IDIALOGUE_H_

#include <combaseapi.h>

interface IDialogue
{
public:
	~IDialogue() = default;

	virtual void PlayDialogue() = 0;
	virtual void PlayDialogue(int dialogueID) = 0;
	virtual void StopDialogue(int dialogueID) = 0;
	virtual void EnableDialogue(int dialogueID) = 0;
	virtual void SetCurrentDialogue(int dialogueID) = 0;
};

#endif
