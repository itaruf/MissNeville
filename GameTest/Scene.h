#pragma once
#ifndef SCENE_H_
#define SCENE_H_

#include <algorithm>
#include <vector>
#include "Puzzle.h"
#include "App/app.h"
#include "Utilities.h"
#include "Dialogues.h"

class Actor;
#include "Actor.h"

class StateController;
class Player;
class Candle;
class Collectable;
class Page;
#include "Page.h"
#include "TriggerScene.h";
#include "Models.h"
#include "TriggerAnimation.h"
#include <random>
#include "Collectable.h"
#include "TriggerScene.h"
// Class which defines a scene : the game is meant to be divided in multiple scenes
class Scene
{
private:
protected:
	int _ID;
	std::vector<Actor*> _actors;
	const char* sfx{SFX.scene};

public:
	Delegate _delegate;
	Vector2D* _startingPos{ nullptr };
	bool initialized{ false };
	Scene* _NScene{ nullptr };
	Scene* _EScene{ nullptr };
	Scene* _WScene{ nullptr };
	Scene* _SScene{ nullptr };

	std::vector<TriggerScene*> doors;

	Scene(int ID);

	virtual ~Scene();

	Actor* GetActor(int index);
	const int& GetID() const;
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