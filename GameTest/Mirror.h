#pragma once
#ifndef MIRROR_H_
#define MIRROR_H_

#include "Collectable.h"
#include "IInteractive.h"
#include "GameState.h"
#include "MirrorShard.h"

// Class defining a candle which has a specific interaction
class Mirror : public Actor, public IInteractive
{
private:
protected:
	bool _repaired{ false };
	static constexpr int nbShards{ 4 };
public:
	Mirror(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~Mirror();

	bool isRepaired();
	void Interact() override;
};

#endif