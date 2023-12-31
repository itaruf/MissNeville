#pragma once
#ifndef MIRROR_H_
#define MIRROR_H_

#include "Collectable.h"
#include "IInteractive.h"
#include "StateController.h"
#include "MirrorShard.h"

// Class defining a candle which has a specific interaction
class Mirror : public Actor, public IInteractive
{
private:
protected:
	bool _repaired{ false };
	static constexpr int nbShards{ 3 };
	const char* _SMirror_repaired{ SFX.mirror_repaired };
public:
	Delegate _onRepaired;

	Mirror(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~Mirror();

	bool isRepaired();
	void Interact() override;
	int GetCollectedMirrorShards();

	inline static constexpr int GetNbShards()
	{
		return nbShards;
	}
};

#endif
