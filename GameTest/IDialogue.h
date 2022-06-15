#pragma once
#ifndef IDIALOGUE_H_

#include <combaseapi.h>

// Set of functions to manage dialogues
interface IDialogue
{
public:
	std::string _currentDialogue;
	std::unordered_map<int, std::string> dialogues;

	~IDialogue() = default;

	virtual void PlayDialogue() = 0;
	virtual void SetCurrentDialogue(int dialogueID)
	{
		if (dialogues.find(dialogueID) != dialogues.end())
			_currentDialogue = dialogues[dialogueID];
	}
};

#endif
