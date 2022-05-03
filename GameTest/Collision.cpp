#include "stdafx.h"
#include "Collision.h"

Collision::Collision(ColliderType colliderType, float height, float width)
	: colliderType{ colliderType }, height{ height }, width{ width }
{
}

bool Collision::isColliding(Actor* character, Actor*& other, float x, float y)
{
	switch (character->direction)
	{
	case Direction::UP:
	case Direction::DOWN:
		if (character->GetPosition().x < other->GetPosition().x + other->GetSprite()->GetWidth() &&
			character->GetPosition().x + character->GetSprite()->GetWidth() > other->GetPosition().x &&
			y < other->GetPosition().y + other->GetSprite()->GetHeight() &&
			character->GetSprite()->GetHeight() + y > other->GetPosition().y)
			return true;
		false;
		break;
	case Direction::LEFT:
	case Direction::RIGHT:
		if (x < other->GetPosition().x + other->GetSprite()->GetWidth() &&
			x + character->GetSprite()->GetWidth() > other->GetPosition().x &&
			character->GetPosition().y < other->GetPosition().y + other->GetSprite()->GetHeight() &&
			character->GetSprite()->GetHeight() + character->GetPosition().y > other->GetPosition().y)
			return true;
		false;
		break;
	default:
		break;
	}
	return false;
}

float& Collision::GetHeight()
{
	return height;
}

void Collision::SetHeight(float value)
{
	height = value;
}

float& Collision::GetWidth()
{
	return width;
}

void Collision::SetWidth(float value)
{
	width = value;
}