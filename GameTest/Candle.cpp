#include "stdafx.h"
#include "Candle.h"

Candle::Candle(std::string name, CSimpleSprite* sprite, Vector2D& position, Collision* collider, Room* currentRoom) : Item(name, sprite, position, collider, currentRoom)
{
	
}

bool Candle::isEnlighted()
{
	return enlighted;
}

void Candle::SetEnlightenment(bool value)
{
	enlighted = value;
}
