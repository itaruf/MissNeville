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
	return _enlighted;
}

// Changing candle's animation when being interacteed with
void Candle::Interact()
{
	if (!_enlighted)
	{
		_enlighted = true;
		_sprite->SetFrame(1);
	}
	else
	{
		_enlighted = false;
		_sprite->SetFrame(0);
	}
}
