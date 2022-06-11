#include "stdafx.h"
#include "Character.h"

Character::Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed) : Actor(name, sprite, position, collider), _HP{ HP }, _movementSpeed{ movementSpeed }
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
	return _HP;
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
	// Setting up the data to match the FORWARDS direction
	if (_direction == Direction::UP)
	{
		_sprite->SetAnimation(_sprite->ANIM_FORWARDS);
		for (const auto& actor : GameState::_currentScene->GetActors())
		{
			// Preventing the player to collide with themselves
			if (actor == this)
				continue;
			// if the player is about to collide with an actor, then the player doesn't move
			if (_collider->isColliding(this, actor, _position->_x, _position->_y + _movementSpeed))
				if (actor->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		_sprite->SetPosition(_position->_x, _position->_y + _movementSpeed);

	}

	else if (_direction == Direction::DOWN)
	{
		// Setting up the data to match the BACKWARDS direction
		_direction = Direction::DOWN;
		_sprite->SetAnimation(_sprite->ANIM_BACKWARDS);
		for (const auto& actor : GameState::_currentScene->GetActors())
		{
			if (actor == this)
				continue;
			if (_collider->isColliding(this, actor, _position->_x, _position->_y - _movementSpeed))
				if (actor->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		_sprite->SetPosition(_position->_x, _position->_y - _movementSpeed);
	}
}

void Character::MoveHorizontally()
{
	if (_direction == Direction::RIGHT)
	{
		std::cout << _name << std::endl;
		// Setting up the data to match the RIGHT direction
		_sprite->SetAnimation(_sprite->ANIM_RIGHT);
		for (const auto& actor : GameState::_currentScene->GetActors())
		{
			if (actor == this)
				continue;
			if (_collider->isColliding(this, actor, _position->_x + _movementSpeed, _position->_y))
				if (actor->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		_sprite->SetPosition(_position->_x + _movementSpeed, _position->_y);
	}

	else if (_direction == Direction::LEFT)
	{
		_sprite->SetAnimation(_sprite->ANIM_LEFT);
		for (const auto& actor : GameState::_currentScene->GetActors())
		{
			if (actor == this)
				continue;
			if (_collider->isColliding(this, actor, _position->_x - _movementSpeed, _position->_y))
				if (actor->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		_sprite->SetPosition(_position->_x - _movementSpeed, _position->_y);
	}
}

// Check if the character is currently moving or not
bool Character::IsMoving()
{
	if (App::GetController().GetLeftThumbStickY() == 0.f && App::GetController().GetLeftThumbStickX() == 0.f)
	{
		_sprite->SetAnimation(-1);
		return false;
	}
	return true;
}