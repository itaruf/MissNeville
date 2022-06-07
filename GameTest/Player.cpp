#include "stdafx.h"
#include "Player.h"

Player::Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed, Inventory* inventory) : Character(name, sprite, position, collider, _HP, movementSpeed), _inventory{ inventory }
{
	// Instantiating all the bags and slots of the inventory
	for (auto i = 0; i < Inventory::_nbBags; ++i)
	{
		_inventory->_bags.insert(std::make_pair(i, std::make_pair(false, std::vector<Collectable*>())));
		for (auto j = 0; j < Inventory::_nbSlotBag; ++j)
			_inventory->_bags[i].second.emplace_back(nullptr);
	}
}

Player::~Player()
{
	printf("CHARACTER DESTRUCTOR CALLED\n");

	// Freeing the memory allocated on the heap
	delete _inventory;
}

// Moving the player on the Y-Axis
void Player::MoveVertically()
{
	// If the player is moving forward
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		// Setting up the data to match the FORWARDS direction
		_direction = Direction::UP;
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
		// else the player can move
		_sprite->SetPosition(_position->_x, _position->_y + _movementSpeed);
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
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

// Moving the player on the X-Axis
void Player::MoveHorizontally()
{
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT) || App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		// Setting up the data to match the RIGHT direction
		_direction = Direction::RIGHT;
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

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		// Setting up the data to match the LEFT direction
		_direction = Direction::LEFT;
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

// Player's main function to interact with other actors and trigger their response to the interaction
bool Player::Interact(IInteractive* actor)
{
	if (GameState::_state != State::REGULAR)
		return false;

	if (!actor)
		return false;

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		if (dynamic_cast<IDialogue*>(actor))
			GameState::SetState(State::DIALOGUE);

		actor->Interact();
		return true;
	}
	return false;
}

// Player's main function to interact with other actors (collectable) and trigger their response to the interaction
bool Player::Interact(Collectable* collectable)
{
	if (GameState::_state != State::REGULAR)
		return false;

	if (!collectable)
		return false;

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		// The collectable is meant to be stored in a dedicated bag (decided with the collectable ID)
		for (auto i = 0; i < _inventory->_bags[collectable->_ID].second.size(); ++i)
		{
			// Looking for the first empty slot
			if (!_inventory->_bags[collectable->_ID].second[i])
			{
				// Stock the collected object in an empty bag slot
				_inventory->_bags[collectable->_ID].second[i] = collectable;
				collectable->itemized = true;
				std::cout << collectable->GetName() << " added in bag " << collectable->_ID << " at slot " << i << std::endl;
				// Removing the actor from the current scene as it is being itemized
				GameState::_currentScene->RemoveActor(collectable);
				return true;
			}
		}
		std::cout << collectable->_ID << std::endl;
		std::cout << collectable->GetName() << " couldn't be added" << std::endl;
	}

	return false;
}

// Open a bag (decided with an ID)
void Player::OpenBag(int ID)
{
	// Check if any bag is opened (can't open multiple bags at the same time)
	if (_inventory->IsAnyBagAlreadyOpened())
		return;

	// Check if the targeted bag already is opened
	if (_inventory->IsBagOpened(ID))
	{
		std::cout << "Bag " << ID << " is aleady opened" << std::endl;
		return;
	}
	
	// The bag is now considered opened
	_inventory->_bags[ID].first = true;
	std::cout << "Bag " << ID << " is now opened" << std::endl;
}

// Close a bag (decided with an ID)
void Player::CloseBag(int ID)
{
	// Check if the bag already is closed
	if (!_inventory->IsBagOpened(ID))
		return;

	// The bag is now considered closed
	_inventory->_bags[ID].first = false;
	std::cout << "Bag " << ID << " is now closed" << std::endl;
}

// Check a specific slot of a specific bag (decided with IDs)
void Player::GoToBagSlot(int ID, int slotNumber)
{
	// Check if the bag exists
	if (!_inventory->IsBagExist(ID))
		return;

	// Check if the bag is opened)
	if (!_inventory->IsBagOpened(ID))
		return;

	// Check if an item is stored at the specific slot
	if (_inventory->GetItem(ID, slotNumber))
		std::cout << _inventory->GetItem(ID, slotNumber)->UseItem() << std::endl;
	else
		std::cout << "No item found at slot " << slotNumber << std::endl;
}

void Player::Interaction()
{
	auto actors{ GameState::_currentScene->GetActors() };

	if (actors.size() <= 0)
		return;

	std::vector<Actor*> interactiveActors{};

	// Select all Collectable or Interactive actors
	for (auto& actor : actors)
		if (dynamic_cast<ICollectable*>(actor) || dynamic_cast<IInteractive*>(actor))
			interactiveActors.emplace_back(actor);

	float ms{ GetMovementSpeed() };

	if (GetDirection() == Direction::LEFT || GetDirection() == Direction::DOWN)
		ms = -GetMovementSpeed();

	float x{ 0 };
	float y{ 0 };

	if (GetDirection() == Direction::RIGHT || GetDirection() == Direction::LEFT)
	{
		x = GetPosition()->_x + ms;
		y = GetPosition()->_y;
	}
	else
	{
		x = GetPosition()->_x;
		y = GetPosition()->_y + ms;
	}

	if (interactiveActors.size() <= 0)
		return;

	/*SORT : FROM CLOSEST ACTOR TO FARTHEST*/
	std::sort(std::begin(interactiveActors), std::end(interactiveActors), [this, ms](Actor* const& l, Actor* const& r)
		{
			return
				std::abs(GetPosition()->_x + ms - l->GetPosition()->_x + ms) + std::abs(GetPosition()->_y + ms - l->GetPosition()->_y + ms)
				<
				std::abs(GetPosition()->_x + ms - r->GetPosition()->_x + ms) + std::abs(GetPosition()->_y + ms - r->GetPosition()->_y + ms);
		});

	auto closestActor = interactiveActors[0];

	App::Print(100, 600, ("Closest Item to Player : " + closestActor->GetName()).c_str());

	/*PLAYER CAN INTERACT WITH ITEMS ONLY IF HE COLLIDES WITH THEM*/

	if (!GetCollider()->isColliding(this, closestActor, x, y))
		return;

	/*INTERACT WITH NON COLLECTIBLE ITEMS*/
	auto interactable = dynamic_cast<IInteractive*>(closestActor);
	if (interactable)
	{
		Interact(interactable);
		return;
	}
	/*COLLECT ITEMS*/
	auto collectable = dynamic_cast<Collectable*>(closestActor);
	if (collectable)
	{
		Interact(collectable);
		return;
	}
}