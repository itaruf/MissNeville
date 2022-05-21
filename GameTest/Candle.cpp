#include "stdafx.h"
#include "Candle.h"

Candle::Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom) : Actor(name, sprite, position, collider, currentRoom)
{
}

Candle::~Candle()
{
	printf("CANDLE DESTRUCTOR CALLED\n");

}

bool Candle::isEnlighted()
{
	return enlighted;
}

void Candle::Interact()
{
	if (!enlighted)
	{
		enlighted = true;
		sprite->SetFrame(1);
	}
	/*else
	{
		enlighted = false;
		sprite->SetFrame(0);
	}*/
}
