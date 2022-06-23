#pragma once
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "Scene.h"
#include "TPPuzzle.h"
#include "StateMain.h"
#include "NPC.h"
#include "StateDialogue.h"
#include "MirrorShard.h"

class StateMain;
// Library scene 
class Library : public Scene, std::enable_shared_from_this<Library>
{
private:
protected:
public:
	TPPuzzle* _TPPuzzle;
	Library(int ID, std::vector<Actor*> actors);
	Library(int ID);
	~Library();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
	bool IsRoomCleared() override;
};

#endif