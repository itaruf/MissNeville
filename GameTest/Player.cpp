#include "stdafx.h"
#include "Player.h"

Player::Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, Scene* currentScene, float HP, float movementSpeed, Inventory* inventory) : Character(name, sprite, position, collider, currentScene, HP, movementSpeed), inventory{ inventory }
{
	// Instantiating all the bags and slots of the inventory
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

	// Freeing the memory allocated on the heap
	delete inventory;
	inventory = nullptr;
}

// Moving the player on the Y-Axis
void Player::MoveVertically()
{
	// If the player is moving forward
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		// Setting up the data to match the FORWARDS direction
		direction = Direction::UP;
		sprite->SetAnimation(sprite->ANIM_FORWARDS);
		for (const auto& actor : currentScene->GetActors())
		{
			// Preventing the player to collide with themselves
			if (actor == this)
				continue;
			// if the player is about to collide with an actor, then the player doesn't move
			if (collider->isColliding(this, actor, position->x, position->y + movementSpeed))
				if (actor->GetCollider()->colliderType == Collision::ColliderType::Block)
					return;
		}
		// else the player can move
		sprite->SetPosition(position->x, position->y + movementSpeed);
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		// Setting up the data to match the BACKWARDS direction
		direction = Direction::DOWN;
		sprite->SetAnimation(sprite->ANIM_BACKWARDS);
		for (const auto& actor : currentScene->GetActors())
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

// Moving the player on the X-Axis
void Player::MoveHorizontally()
{
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT) || App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		// Setting up the data to match the RIGHT direction
		direction = Direction::RIGHT;
		sprite->SetAnimation(sprite->ANIM_RIGHT);
		for (const auto& actor : currentScene->GetActors())
		{
			if (actor == this)
				continue;
			if (collider->isColliding(this, actor, position->x + movementSpeed, position->y))
				if (actor->GetCollider()->colliderType == Collision::ColliderType::Block)
					return;
		}
		sprite->SetPosition(position->x + movementSpeed, position->y);
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		// Setting up the data to match the LEFT direction
		direction = Direction::LEFT;
		sprite->SetAnimation(sprite->ANIM_LEFT);
		for (const auto& actor : currentScene->GetActors())
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

// Player's main function to interact with other actors and trigger their response to the interaction
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

// Player's main function to interact with other actors (collectable) and trigger their response to the interaction
bool Player::Interact(Collectable* collectable)
{
	if (!collectable)
		return false;

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		// The collectable is meant to be stored in a dedicated bag (decided with the collectable ID)
		for (auto i = 0; i < inventory->bags[i].second.size(); ++i)
		{
			// Looking for the first empty slot
			if (!inventory->bags[collectable->ID].second[i])
			{
				// Stock the collected object in an empty bag slot
				inventory->bags[collectable->ID].second[i] = collectable->Collect();
				std::cout << collectable->GetName() << " added in bag " << collectable->ID << " at slot " << i << std::endl;
				// Removing the actor from the current scene as it is being itemized
				currentScene->RemoveActor(collectable);
				collectable = nullptr;
				return true;
			}
		}
		std::cout << collectable->GetName() << " couldn't be added" << std::endl;
	}

	collectable = nullptr;
	return false;
}

// Open a bag (decided with an ID)
void Player::OpenBag(int ID)
{
	// Check if any bag is opened (can't open multiple bags at the same time)
	if (inventory->IsAnyBagAlreadyOpened())
		return;

	// Check if the targeted bag already is opened
	if (inventory->IsBagOpened(ID))
	{
		std::cout << "Bag " << ID << " is aleady opened" << std::endl;
		return;
	}
	
	// The bag is now considered opened
	inventory->bags[ID].first = true;
	std::cout << "Bag " << ID << " is now opened" << std::endl;
}

// Close a bag (decided with an ID)
void Player::CloseBag(int ID)
{
	// Check if the bag already is closed
	if (!inventory->IsBagOpened(ID))
		return;

	// The bag is now considered closed
	inventory->bags[ID].first = false;
	std::cout << "Bag " << ID << " is now closed" << std::endl;
}

// Check a specific slot of a specific bag (decided with IDs)
void Player::GoToBagSlot(int ID, int slotNumber)
{
	// Check if the bag exists
	if (inventory->IsBagExist(ID))
	{
		// Check if the bag is opened)
		if (inventory->IsBagOpened(ID))
		{
			// Check if an item is stored at the specific slot
			if (inventory->GetItem(ID, slotNumber))
				std::cout << inventory->GetItem(ID, slotNumber)->description << std::endl;
			else 
				std::cout << "No item found at slot " << slotNumber << std::endl;
		}
	}
}