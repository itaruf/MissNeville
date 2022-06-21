#pragma once

#ifndef LETHAL_H_
#define LETHAL_H_

#include "Actor.h"

class Lethal : public Actor
{
private:
protected:
public:
	Delegate _delegate;
	Lethal(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~Lethal();
};

#endif