#pragma once
#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include "Actor.h"
#include "ICollectable.h"

// Actor which can be collected by the player and itemized
class Collectable : public Actor, public ICollectable
{
private:
protected:
public:
	Delegate _delegate;
	int _ID;
	std::string _description;
	bool itemized = false;
	const char* _SCollected{ SFX.item_pick2 };
	const char* _SUsed{ SFX.item_pick2 };
	Collectable(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, int ID = 0, std::string description = "");
	~Collectable();

	// Each Collectable will have its own treatment
	void OnCollected();
	virtual bool UseItem() = 0;
};

#endif