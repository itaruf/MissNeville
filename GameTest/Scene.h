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

class StateMain;
class Player;
class Candle;
class Collectable;
class Page;
#include "Page.h"
#include "TriggerScene.h";
#include "Models.h"
#include "TriggerAnimation.h"
#include <random>

// Class which defines a scene : the game is meant to be divided in multiple scenes
class Scene
{
private:
protected:
	int _ID;
	CSimpleSprite* _background{ nullptr };
	std::vector<Actor*> _actors;
	const char* sfx{SFX.scene};

public:
	Delegate _delegate;

	bool initialized{ false };
	Scene* _NScene{ nullptr };
	Scene* _EScene{ nullptr };
	Scene* _WScene{ nullptr };
	Scene* _SScene{ nullptr };

	std::vector<TriggerScene*> doors;

	Scene(int ID, std::vector<Actor*> actors);
	Scene(int ID);

	virtual ~Scene();

	Actor* GetActor(int index);
	const int& GetID() const;
	std::vector<Actor*>& GetActors();
	bool RemoveActor(Actor* item);
	void AddActor(Actor* actor);
	bool RemoveActor(Collectable* collectable);

	virtual bool Init() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual bool IsRoomCleared() = 0;
	virtual void OnMirrorShattered();

};

#endif