#pragma once
#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include "../../Actors/Actor.h"
#include "../../Interfaces/ICollectable.h"
#include "../../Utilities/Maths/Vector2D.h"
#include "../../Utilities/Models.h"

// Actor which can be collected by the player and itemized
class Collectable : public Actor, public ICollectable
{
public:
	Delegate onCollected;
	const char* _SCollected{ SFX.item_pick2 };
	const char* _SUsed{ SFX.item_pick2 };
protected:
	int _ID;
	std::string _description;
	bool _itemized = false;
public:
	Collectable(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, int ID = 0, std::string description = "");
	~Collectable();

	int GetID();
	bool isItemized();

	void OnCollected();

	// Each Collectable will have its own treatment
	virtual void UseItem();
};

#endif