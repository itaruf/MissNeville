#pragma once
#ifndef CANDLE_H_
#define CANDLE_H_

#include "../../Actors/Collectibles/Collectable.h"
#include "../../Interfaces/IInteractive.h"

// Class defining a candle which has a specific interaction
class Candle : public Actor, public IInteractive
{
protected:
	bool _enlighted{ false };
public:	
	const char* _SEnlight{SFX.candle_enlight};
	const char* _SShut{ SFX.candle_enlight };
public:
	Candle(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider);
	~Candle();

	void Interact() override;

	bool isEnlighted();
};

#endif