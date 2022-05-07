#pragma once
#ifndef CANDLE_H_
#define CANDLE_H_

#include "Item.h"

class Candle : Item
{
private:
protected:
	bool enlighted;
public:
	Candle(std::string name, CSimpleSprite* sprite, Vector2D& position, Collision* collider, Room* currentRoom);
	~Candle() = default;
	bool isEnlighted();
	void SetEnlightenment(bool value);
};

#endif
