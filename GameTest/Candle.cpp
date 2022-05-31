#include "stdafx.h"
#include "Candle.h"

Candle::Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Actor(name, sprite, position, collider)
{
}

Candle::~Candle()
{
	printf("CANDLE DESTRUCTOR CALLED\n");

}

// Get the current enlightnement of the candle
bool Candle::isEnlighted()
{
	return enlighted;
}

// Changing candle's animation when being interacteed with
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
