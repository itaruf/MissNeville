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
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f)
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

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
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
	// D or LeftThumbStick X
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT) || App::GetController().GetLeftThumbStickX() > 0.5f)
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

	// Q or LeftThumbStick X
	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
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

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		actor->Interact();
		actor = nullptr;
		return true;
	}
	actor = nullptr;
	return false;
}

bool Character::Interact(Collectable* collectable)
{
	if (!collectable)
		return false;

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		inventory->bags[collectable->ID].second.emplace_back(collectable->Collect());
		currentRoom->RemoveActor(collectable);
		collectable = nullptr;
		return true;
	}
	collectable = nullptr;
	return false;
}

void Character::OpenInventory(int ID)
{
	if (!inventory->IsBagExist(ID))
		return;

	if (isBagOpened(ID))
		CloseInventory(ID);

	else
	{
		// the inventory at ID is now considered opened
		inventory->bags[ID].first = true;
		printf("Bag %d is now opened", ID);
	}
}

void Character::CloseInventory(int ID)
{
	if (!inventory->IsBagExist(ID))
		return;

	if (!isBagOpened(ID))
		return;

	// the inventory at ID is now considered closed
	inventory->bags[ID].first = false;
	printf("Bag %d is now closed", ID);
}

bool Character::isBagOpened(int ID)
{
	if (inventory->IsBagExist(ID))
	{
		return inventory->bags[ID].first;
	}
	return false;
}

void Character::GoToBagSlot(int ID, int slotNumber)
{
	if (isBagOpened(ID))
	{
		std::cout << inventory->GetItem(ID, slotNumber)->description << std::endl;
	}
}


float Character::GetGrabRange()
{
	return grabRange;
}
