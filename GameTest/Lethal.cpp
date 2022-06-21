#include "../stdafx.h"
#include "Lethal.h"

Lethal::Lethal(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Actor(name, sprite, position, collider)
{
}

Lethal::~Lethal()
{
}
