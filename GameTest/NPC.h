#pragma once
#ifndef NPC_H_
#define NPC_H_

#include "Character.h"

class NPC : public Character
{
private:
protected:
public:
	NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed);
	~NPC();
};

#endif
