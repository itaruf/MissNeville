#pragma once
#ifndef STATEREGULAR_H_
#define STATEREGULAR_H_

#include "GameState.h"

class StateRegular : public GameState
{
public:
	StateRegular() = default;
	~StateRegular() = default;

	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

#endif 