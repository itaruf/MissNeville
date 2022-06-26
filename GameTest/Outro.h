#pragma once
#ifndef OUTRO_H_
#define OUTRO_H_

#include "Scene.h"
#include "StateMain.h"
#include "Dialogues.h"

class StateMain;
// Outro scene 
class Outro : public Scene
{
private:
protected:
public:
	Outro(int ID);
	~Outro();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;

};

#endif