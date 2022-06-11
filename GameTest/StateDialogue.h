#pragma once
#ifndef STATEDIALOGUE_H_
#define STATEDIALOGUE_H_

#include "GameStateController.h"

class StateDialogue : public GameStateController
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