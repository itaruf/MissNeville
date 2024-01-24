#pragma once
#ifndef INTRO_H_
#define INTRO_H_

#include "../Systems/Dialogues/Dialogues.h"
#include "../Systems/States/StateController.h"

#include "Scene.h"

// Intro scene 
class Intro : public Scene
{
public:
	Intro(int ID);
	~Intro() = default;

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override; 
	void Exit() override;
	bool IsRoomCleared() override;

};

#endif