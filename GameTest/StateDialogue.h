#pragma once
#ifndef STATEDIALOGUE_H_
#define STATEDIALOGUE_H_

#include "StateController.h"

class StateDialogue : public StateController
{
public:
	std::string _currentDialogue = " ";
	CSimpleSprite* _dialogueBox;
	StateDialogue(CSimpleSprite* dialogueBox);
	~StateDialogue();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

#endif