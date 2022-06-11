#pragma once

#ifndef MIRRORSHARD_H
#define MIRRORSHARD_H

#include "Collectable.h"

class MirrorShard : public Collectable
{
private:
protected:
public:
	MirrorShard(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, int ID = 0, std::string description = " ");
	~MirrorShard();

	bool UseItem() override;
};

#endif
