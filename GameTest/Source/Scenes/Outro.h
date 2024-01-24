#pragma once
#ifndef OUTRO_H_
#define OUTRO_H_

#include "../Systems/Dialogues/Dialogues.h"
#include "../Systems/States/StateController.h"

#include "Scene.h"

// Outro scene 
class Outro : public Scene
{
public:
	Outro(int ID);
	~Outro() = default;

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;

	bool IsRoomCleared() override;
};

#endif