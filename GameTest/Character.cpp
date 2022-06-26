#include "../stdafx.h"
#include "Character.h"

//CSimpleSound& Character::_SFXDeath = CSimpleSound::GetInstance();
//CSimpleSound& Character::_SFXInteract = CSimpleSound::GetInstance();

Character::Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed, Controller* controller) : Actor(name, sprite, position, collider), _HP{ HP }, _movementSpeed{ movementSpeed }, _controller{controller}
{
	/*_footStep = new CSimpleSprite(MBlood.model);*/
	/*std::cout << "CHARACTER CONSTRUCTOR CALLED" << std::endl;*/
	/*_SFXInteract = new CSimpleSound(SFX.item_pick);*/
}

Character::~Character()
{
	printf("CHARACTER DESTRUCTOR CALLED\n");

	if (_controller)
		delete _controller;

	if (_footStep)
		delete _footStep;
}

// Get the current HP of the character
const float& Character::GetHP() const
{
	return _HP;
}

Controller* Character::GetController() const
{
	return _controller;
}

// Set the HP of the character
void Character::SetHP(float value)
{
	_HP = value;
}

// Get the curret movement speed of the character
const float& Character::GetMovementSpeed() const
{
	return _movementSpeed;
}

// Set the movementspeed of the character
void Character::SetMovementSpeed(float value)
{
	_movementSpeed = value;
}

void Character::MoveVertically()
{
	if (!_controller)
		return;

	_controller->MoveVertically(this);
}

void Character::MoveHorizontally()
{
	if (!_controller)
		return;

	_controller->MoveHorizontally(this);
}

// Check if the character is currently moving or not
bool Character::IsMoving()
{
	if (App::GetController().GetLeftThumbStickY() == 0.f && App::GetController().GetLeftThumbStickX() == 0.f)
	{
		/*_direction = Direction::STILL;*/
		if (_sprite->GetCurrentAnim() == -1)
			return false;

		_sprite->SetFrame(_sprite->GetAnimations()[_sprite->GetCurrentAnim()].m_frames[0]);
		_sprite->SetAnimation(-1);
		return false;
	}
	return true;
}