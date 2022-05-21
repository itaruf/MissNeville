#pragma once
#ifndef CANDLE_H_
#define CANDLE_H_

#include "Collectable.h"
#include "IInteractive.h"

class Candle : public Actor, public IInteractive
{
private:
protected:
	bool enlighted = false;
public:
	Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom);
	~Candle();

	bool isEnlighted();
	/*void Enlight(bool value);*/
	void Interact() override;
};

#endif