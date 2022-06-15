#pragma once
#ifndef IDIALOGUE_H_

#include <combaseapi.h>

// Set of functions to manage dialogues
interface IDialogue
{
public:
	~IDialogue() = default;

	virtual void PlayDialogue() = 0;
	virtual void SetCurrentDialogue(int dialogueID) = 0;
};

#endif
