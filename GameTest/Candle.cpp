#include "stdafx.h"
#include "Candle.h"

Candle::Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, std::shared_ptr<Room> currentRoom, Interactivity interactivity) : Item(name, sprite, position, collider, currentRoom, interactivity)
{
}

bool Candle::isEnlighted()
{
	return enlighted;
}

void Candle::SetEnlightenment(bool value)
{
	if (!enlighted) 
	{
		enlighted = true;
		sprite->SetFrame(1);
	}
	else
	{
		enlighted = false;
		sprite->SetFrame(0);
	}
}
