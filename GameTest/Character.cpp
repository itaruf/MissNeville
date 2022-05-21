#include "stdafx.h"
#include "Character.h"

Character::Character(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed, Inventory* inventory) : Actor(name, sprite, position, collider, currentRoom), HP{ HP }, movementSpeed{ movementSpeed }, inventory{ inventory }
{
}

Character::~Character()
{
	printf("CHARACTER DESTRUCTOR CALLED\n");
	delete inventory;
	inventory = nullptr;
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

void Character::MoveVertically()
{
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		direction = Direction::UP;
		sprite->SetAnimation(sprite->ANIM_FORWARDS);
		for (const auto& actor : currentRoom->GetActors())
		{
			if (actor == this)
				continue;
			if (collider->isColliding(this, actor, position->x, position->y + movementSpeed))
				if (actor->GetCollider()->colliderType == Collision::ColliderType::Block)
					return;
		}
		sprite->SetPosition(position->x, position->y + movementSpeed);
	}

	else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		direction = Direction::DOWN;
		sprite->SetAnimation(sprite->ANIM_BACKWARDS);
		for (const auto& actor : currentRoom->GetActors())
		{
			if (actor == this)
				continue;
			if (collider->isColliding(this, actor, position->x, position->y - movementSpeed))
				if (actor->GetCollider()->colliderType == Collision::ColliderType::Block)
					return;
		}
		sprite->SetPosition(position->x, position->y - movementSpeed);
	}
}

void Character::MoveHorizontally()
{
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		direction = Direction::RIGHT;
		sprite->SetAnimation(sprite->ANIM_RIGHT);
		for (const auto& actor : currentRoom->GetActors())
		{
			if (actor == this)
				continue;
			if (collider->isColliding(this, actor, position->x + movementSpeed, position->y))
				if (actor->GetCollider()->colliderType == Collision::ColliderType::Block)
					return;
		}
		sprite->SetPosition(position->x + movementSpeed, position->y);
	}

	else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		direction = Direction::LEFT;
		sprite->SetAnimation(sprite->ANIM_LEFT);
		for (const auto& actor : currentRoom->GetActors())
		{
			if (actor == this)
				continue;
			if (collider->isColliding(this, actor, position->x - movementSpeed, position->y))
				if (actor->GetCollider()->colliderType == Collision::ColliderType::Block)
					return;
		}
		sprite->SetPosition(position->x - movementSpeed, position->y);
	}
}

//bool Character::UseLighter(Candle* candle)
//{
//	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
//	{
//		if (!candle)
//			return false;
//
//		if (candle->isEnlighted())
//		{
//			candle = nullptr;
//			return false;
//		}
//
//		candle->Enlight(true);
//		candle = nullptr;
//		return true;
//	}
//	candle = nullptr;
//	return false;
//}

bool Character::Interact(int ID, IInteractive* actor)
{
	if (!actor)
		return false;

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		actor->Interact();
		actor = nullptr;
		return true;
	}
	actor = nullptr;
	return false;
}

bool Character::Interact(int ID, ICollectable* collectable)
{
	if (!collectable)
		return false;

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		inventory->items[ID].emplace_back(collectable->Collect());
		currentRoom->RemoveActor(dynamic_cast<Actor*>(collectable));
		collectable = nullptr;
		return true;
	}
	collectable = nullptr;
	return false;
}


float Character::GetGrabRange()
{
	return grabRange;
}
