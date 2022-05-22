#include "stdafx.h"
#include "Character.h"

Character::Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed) : Actor(name, sprite, position, collider, currentRoom), HP{ HP }, movementSpeed{ movementSpeed }
{
	/*std::cout << "CHARACTER CONSTRUCTOR CALLED" << std::endl;*/
}

Character::~Character()
{
	printf("CHARACTER DESTRUCTOR CALLED\n");
}

const float& Character::GetHP() const
{
	return HP;
}

void Character::SetHP(float value)
{
	HP = value;
}

const float& Character::GetMovementSpeed() const
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
		sprite->SetAnimation(-1);
		return false;
	}
	return true;
}