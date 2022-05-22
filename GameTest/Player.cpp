#include "stdafx.h"
#include "Player.h"

Player::Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Room* currentRoom, float HP, float movementSpeed, Inventory* inventory) : Character(name, sprite, position, collider, currentRoom, HP, movementSpeed), inventory{ inventory }
{
	for (auto i = 0; i < Inventory::nbBags; ++i)
	{
		inventory->bags.insert(std::make_pair(i, std::make_pair(false, std::vector<InventoryItem*>())));
		for (auto j = 0; j < Inventory::nbSlotBag; ++j)
		{
			inventory->bags[i].second.emplace_back(nullptr);
		}
	}

}

Player::~Player()
{
	printf("CHARACTER DESTRUCTOR CALLED\n");
	delete inventory;
	inventory = nullptr;
}

bool Player::isMoving()
{
	if (App::GetController().GetLeftThumbStickY() == 0.f && App::GetController().GetLeftThumbStickX() == 0.f)
	{
		sprite->SetAnimation(-1);
		return false;
	}
	return true;
}

void Player::MoveVertically()
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

void Player::MoveHorizontally()
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

//bool Player::UseLighter(Candle* candle)
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

bool Player::Interact(IInteractive* actor)
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

bool Player::Interact(Collectable* collectable)
{
	if (!collectable)
		return false;

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		for (auto i = 0; i < inventory->bags[i].second.size(); ++i)
		{
			if (!inventory->bags[collectable->ID].second[i])
			{
				// Stock the collected object in an empty bag slot
				inventory->bags[collectable->ID].second[i] = collectable->Collect();
				std::cout << collectable->GetName() << " added in bag " << 1 << " at slot " << i << std::endl;
				currentRoom->RemoveActor(collectable);
				collectable = nullptr;
				return true;
			}
		}
		std::cout << collectable->GetName() << " couldn't be added" << std::endl;
	}

	collectable = nullptr;
	return false;
}

void Player::OpenInventory(int ID)
{
	if (inventory->IsAnyBagAlreadyOpened())
		return;

	if (inventory->IsBagOpened(ID))
	{
		std::cout << "Bag " << ID << " is aleady opened" << std::endl;
		return;
	}
	
	// the bag is now considered opened
	inventory->bags[ID].first = true;
	std::cout << "Bag " << ID << " is now opened" << std::endl;
}

void Player::CloseInventory(int ID)
{
	if (!inventory->IsBagOpened(ID))
		return;

	// the bag is now considered closed
	inventory->bags[ID].first = false;
	std::cout << "Bag " << ID << " is now closed" << std::endl;
}

void Player::GoToBagSlot(int ID, int slotNumber)
{
	if (inventory->IsBagExist(ID))
	{
		if (inventory->IsBagOpened(ID))
		{
			if (inventory->GetItem(ID, slotNumber))
				std::cout << inventory->GetItem(ID, slotNumber)->description << std::endl;
			else 
				std::cout << "not item found at slot " << slotNumber << std::endl;
		}
	}
}


float Player::GetGrabRange()
{
	return grabRange;
}
