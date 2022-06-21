#pragma once
#ifndef CANDLE_H_
#define CANDLE_H_

#include "Collectable.h"
#include "IInteractive.h"

// Class defining a candle which has a specific interaction
class Candle : public Actor, public IInteractive
{
private:
protected:
	bool _enlighted{ false };
public:
	
	const char* _SEnlight{SFX.candle_enlight};
	const char* _SShut{ SFX.candle_enlight };
	Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider);
	~Candle();

	bool isEnlighted();
	void Interact() override;
	void OnInteract() override;
};

#endif