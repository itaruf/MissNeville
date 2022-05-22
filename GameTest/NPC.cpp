#include "stdafx.h"
#include "NPC.h"

NPC::NPC(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed) 
	: Character(name, sprite, position, collider, currentRoom, HP, movementSpeed)
{
}

NPC::~NPC()
{
}
