#include "stdafx.h"
#include "Character.h"

Character::Character(std::string name, CSimpleSprite*& sprite, Vector2D& position, Collision*& collider, Room* currentRoom, float HP, float movementSpeed) : Actor(name, sprite, position, collider, currentRoom), HP{ HP }, movementSpeed{ movementSpeed }
{
}

float& Character::GetHP()
{
	return HP;
}

void Character::SetHP(float value)
{
	HP = value;
}

float& Character::GetMovementSpeed()
{
	return movementSpeed;
}

void Character::SetMovementSpeed(float value)
{
	movementSpeed = value;
}

bool Character::isMoving()
{
	if (App::GetController().GetLeftThumbStickY() == 0.f && App::GetController().GetLeftThumbStickX() == 0.f)
	{
		direction = Direction::STILL;
		sprite->SetAnimation(-1);
		return false;
	}
	return true;
}

void Character::MoveVertically()
{
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		direction = Direction::UP;
		sprite->SetAnimation(sprite->ANIM_FORWARDS);
		for (int i = 0; i < currentRoom->GetActors().size(); i++) 
		{
			if (collider->isColliding(this, currentRoom->GetActor(i), position.x, position.y + movementSpeed))
			return;
		}
		sprite->SetPosition(position.x, position.y + movementSpeed);
	}

	else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		direction = Direction::DOWN;
		sprite->SetAnimation(sprite->ANIM_BACKWARDS);
		for (int i = 0; i < currentRoom->GetActors().size(); i++) 
		{
			if (collider->isColliding(this, currentRoom->GetActor(i), position.x, position.y - movementSpeed))
			return;
		}
		sprite->SetPosition(position.x, position.y - movementSpeed);
	}
}

void Character::MoveHorizontally()
{
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		direction = Direction::RIGHT;
		sprite->SetAnimation(sprite->ANIM_RIGHT);
		for (int i = 0; i < currentRoom->GetActors().size(); i++) 
		{
			if (collider->isColliding(this, currentRoom->GetActor(i), position.x + movementSpeed, position.y))
			return;
		}
		sprite->SetPosition(position.x + movementSpeed, position.y);
	}

	else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		direction = Direction::LEFT;
		sprite->SetAnimation(sprite->ANIM_LEFT);
		for (int i = 0; i < currentRoom->GetActors().size(); i++) 
		{
			if (collider->isColliding(this, currentRoom->GetActor(i), position.x - movementSpeed, position.y))
			return;
		}
		sprite->SetPosition(position.x - movementSpeed, position.y);
	}
}