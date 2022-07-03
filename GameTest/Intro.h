#pragma once
#ifndef INTRO_H_
#define INTRO_H_

#include "Scene.h"
#include "StateController.h"
#include "Dialogues.h"

class StateController;
// Intro scene 
class Intro : public Scene
{
private:
protected:
public:
	Intro(int ID);
	~Intro();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override; 
	void Exit() override;
	bool IsRoomCleared() override;

};

#endif