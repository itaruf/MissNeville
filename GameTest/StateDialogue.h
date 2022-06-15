#pragma once
#ifndef STATEDIALOGUE_H_
#define STATEDIALOGUE_H_

#include "StateController.h"

class StateDialogue : public StateController
{
public:
	std::string _currentDialogue = " ";
	CSimpleSprite* _dialogueBox;

	const int maxChar{ 50 };
	const int maxLines{ 3 };
	std::vector<std::string> subDialogues;

	StateDialogue(CSimpleSprite* dialogueBox);
	~StateDialogue();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

#endif