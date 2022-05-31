#include "stdafx.h"
#include "Character.h"

Character::Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed) : Actor(name, sprite, position, collider), HP{ HP }, movementSpeed{ movementSpeed }
{
	/*std::cout << "CHARACTER CONSTRUCTOR CALLED" << std::endl;*/
}

Character::~Character()
{
	printf("CHARACTER DESTRUCTOR CALLED\n");
}

// Get the current HP of the character
const float& Character::GetHP() const
{
	return HP;
}

// Set the HP of the character
void Character::SetHP(float value)
{
	HP = value;
}

// Get the curret movement speed of the character
const float& Character::GetMovementSpeed() const
{
	return movementSpeed;
}

// Set the movementspeed of the character
void Character::SetMovementSpeed(float value)
{
	movementSpeed = value;
}

// Check if the character is currently moving or not
bool Character::IsMoving()
{
	if (App::GetController().GetLeftThumbStickY() == 0.f && App::GetController().GetLeftThumbStickX() == 0.f)
	{
		sprite->SetAnimation(-1);
		return false;
	}
	return true;
}