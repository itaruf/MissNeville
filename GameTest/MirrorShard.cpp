#include "../stdafx.h"
#include "MirrorShard.h"

MirrorShard::MirrorShard(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, int ID, std::string description) : Collectable(name, sprite, position, collider, ID, description)
{
}

MirrorShard::~MirrorShard()
{
}

bool MirrorShard::UseItem()
{
	std::cout << _description << std::endl;
	return true;
}
