#pragma once
#ifndef SCENE_H_
#define SCENE_H_

#include "App/app.h"

#include "Actor.h"
#include "Collectable.h"
#include "Dialogues.h"
#include "Models.h"
#include "Page.h"
#include "Puzzle.h"
#include "TriggerAnimation.h"
#include "TriggerScene.h"
#include "Utilities.h"

#include <algorithm>
#include <random>
#include <vector>

class Actor;
class Candle;
class Collectable;
class Page;
class Player;
class StateController;

// Class which defines a scene : the game is meant to be divided in multiple scenes
class Scene
{
protected:
	int _ID;
	std::vector<Actor*> _actors;
	const char* sfx{SFX.scene};
public:
	Delegate _delegate;
	Vector2D _startingPos{ 0,0 };

	bool initialized{ false };

	Scene* _NScene{ nullptr };
	Scene* _EScene{ nullptr };
	Scene* _WScene{ nullptr };
	Scene* _SScene{ nullptr };

	std::vector<TriggerScene*> doors;
public:
	Scene(int ID);
	virtual ~Scene();

	int GetID() const;

	Actor* GetActor(int index);
	std::vector<Actor*>& GetActors();
	bool RemoveActor(Actor* item);
	void AddActor(Actor* actor);
	bool RemoveActor(Collectable* collectable);

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual bool IsRoomCleared() = 0;
	virtual void Exit() = 0;

};

#endif