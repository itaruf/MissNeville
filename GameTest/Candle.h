#pragma once
#ifndef CANDLE_H_
#define CANDLE_H_

#include "Item.h"

class Candle : public Item
{
private:
protected:
	bool enlighted = false;
public:
	Candle(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, std::shared_ptr<Room> currentRoom, Interactivity interactivity);
	~Candle() = default;

	bool isEnlighted();
	void Enlight(bool value);
};

#endif

