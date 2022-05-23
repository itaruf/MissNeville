#pragma once
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Scene.h"
#include "Entrance.h"
#include "Player.h"

class Scene;
class Entrance;
class Player;

// Class in charge of managing the current state of the game and navigating through rooms
class GameState
{
private:
protected:
public:
	Scene* currentScene;
	std::vector<Scene*> rooms;
	Player* player{ nullptr };

	GameState();
	GameState(std::vector<Scene*>& rooms);
	GameState(Scene* currentScene, std::vector<Scene*>& rooms);
	GameState(Scene* currentScene);
	~GameState();

	Player* GetPlayer();
	void AddPlayer(Player* player);
};

#endif