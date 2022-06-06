#pragma once
#include "GameStateController.h"
class StateDialogue : public GameStateController
{
public:
	StateDialogue();
	~StateDialogue();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

