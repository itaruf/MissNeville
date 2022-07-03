#pragma once
#ifndef STATEDIALOGUE_H_
#define STATEDIALOGUE_H_

#include "GameState.h"
#include "Utilities.h"
#include <exception>

class StateDialogue : public GameState
{
public:
	std::vector<std::string> _currentDialogue;
	CSimpleSprite* _dialogueBox;
	Delegate _onDialogueEnd;

	const int maxChar{ 45 };
	const int maxLines{ 3 };
	int start{ 0 };
	int end{ 0 };
	int remainingDials{ 0 };
	std::string speaker{ " " };
	std::vector<std::string> subDialogues;

	StateDialogue(CSimpleSprite* dialogueBox);
	~StateDialogue();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
	void ProcessDialogue(std::string dialogue);
	void ForceLineWrap(std::string dialogue);
	void LineWrap(std::string dialogue, size_t pos);
	void Clear();
};

#endif