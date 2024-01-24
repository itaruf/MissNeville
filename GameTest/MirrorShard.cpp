#include "../stdafx.h"
#include "MirrorShard.h"

MirrorShard::MirrorShard(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, int ID, std::string description) : Collectable(name, sprite, position, collider, ID, description)
{
	_SCollected = SFX.mshard_pick;
}

void MirrorShard::UseItem()
{
	Collectable::UseItem();
}