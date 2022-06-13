#pragma once
#ifndef SCENE_H_
#define SCENE_H_

#include <algorithm>
#include <vector>
#include "Puzzle.h"
#include "App/app.h"
#include "Utilities.h"
class Actor;
#include "Actor.h"

class GameState;
class Player;
class Candle;
class Collectable;
class Page;
#include "Page.h"

// Class which defines a scene : the game is meant to be divided in multiple scenes
class Scene
{
private:
protected:
	int _ID;
	CSimpleSprite* _background{ nullptr };
	std::vector<Actor*> _actors;

public:

	bool initialized{ false };
	Scene* _NScene{ nullptr };
	Scene* _EScene{ nullptr };
	Scene* _WScene{ nullptr };
	Scene* _SScene{ nullptr };

	Scene(int ID, std::vector<Actor*> actors);
	Scene(int ID);

	virtual ~Scene();

	Actor* GetActor(int index);
	const int& GetID() const;
	std::vector<Actor*>& GetActors();
	bool RemoveActor(Actor* item);
	void AddActor(Actor* actor);
	bool RemoveActor(Collectable* collectable);

	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual bool IsRoomCleared() = 0;
};

#endif