#pragma once
#ifndef STATEREGULAR_H_
#define STATEREGULAR_H_

#include "StateController.h"

class StateRegular : public StateController
{
public:

	StateRegular();
	~StateRegular();
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

#endif 