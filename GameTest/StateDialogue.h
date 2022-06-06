#pragma once
#ifndef STATEDIALOGUE_H_
#define STATEDIALOGUE_H_

class GameStateController;
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

#endif