#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

class Scene;
#include "Scene.h"

class Entrance;
#include "Entrance.h"

class Player;
#include "Player.h"

class GameStateController;
#include "GameStateController.h"


// Class in charge of managing the current state of the game and navigating through rooms
class GameState
{
private:
protected:
public:
	static Scene* currentScene;
	static std::vector<Scene*> rooms;
	static Player* player;
	/*static */std::vector<GameStateController*> gameStates;
	/*static */GameStateController* currentState;

	GameState();
	~GameState();

	Player* GetPlayer();
	void AddPlayer(Player* player);
};

#endif