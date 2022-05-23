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
	bool enlighted = false;
public:
	Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* currentScene);
	~Candle();

	bool isEnlighted();
	void Interact() override;
};

#endif