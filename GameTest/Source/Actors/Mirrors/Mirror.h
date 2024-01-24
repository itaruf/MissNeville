#pragma once
#ifndef MIRROR_H_
#define MIRROR_H_

#include "../../Actors/Collectibles/Collectable.h"
#include "../../Actors/Collectibles/MirrorShard.h"
#include "../../Interfaces/IInteractive.h"
#include "../../Systems/States/StateController.h"

// Class defining a candle which has a specific interaction
class Mirror : public Actor, public IInteractive
{
protected:
	bool _repaired{ false };
	static constexpr int nbShards{ 3 };
	const char* _SMirror_repaired{ SFX.mirror_repaired };
public:
	Delegate onRepaired;
public:

	Mirror(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider);
	~Mirror();

	void Interact() override;

	bool isRepaired();
	void SetRepaired(bool value);
	int GetCollectedMirrorShards();
	int GetNbShards();
};

#endif