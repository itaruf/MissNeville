#pragma once
#ifndef SCENE_H_
#define SCENE_H_

#include <algorithm>
#include <vector>
#include "Puzzle.h"
class Actor;
//#include "Actor.h"
#include "App/app.h"

class GameState;
class Player;
class Candle;
class Collectable;

// Class which defines a scene : the game is meant to be divided in multiple scenes
class Scene
{
private:
protected:
	int _ID;
	CSimpleSprite* _background{ nullptr };
	std::vector<Actor*> _actors;

public:

	Scene* NScene{ nullptr };
	Scene* EScene{ nullptr };
	Scene* WScene{ nullptr };
	Scene* SScene{ nullptr };

	Scene(int ID, std::vector<Actor*> actors);
	Scene(int ID);

	virtual ~Scene();

	Actor* GetActor(int index);
	const int& GetID() const;
	std::vector<Actor*>& GetActors();
	bool RemoveActor(Actor* item);
	void AddActor(Actor* actor);
	bool RemoveActor(Collectable* collectable);

	virtual void Init() = 0;
	virtual void Update(float deltaTime);
	virtual void Render() = 0;
	virtual bool IsRoomCleared() = 0;
};

#endif