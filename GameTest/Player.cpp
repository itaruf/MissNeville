#include "../stdafx.h"
#include "Player.h"

Player::Player(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider, float HP, float movementSpeed, Controller* controller, Inventory* inventory) : Character(name, sprite, position, collider, _HP, movementSpeed, controller), _inventory{ inventory }
{
	/*_SFXInteract = CSimpleSound::GetInstance();
	_SFXDeath = CSimpleSound::GetInstance();*/

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

	if (_inventory)
		delete _inventory;

	/*if (_SBag)
		delete[] _SBag;

	if (_SCollect)
		delete[] _SCollect;*/
}

// Moving the player on the Y-Axis
void Player::MoveVertically()
{
	if (!_controller)
		return;

	_controller->MoveVertically(this);
}

// Moving the player on the X-Axis
void Player::MoveHorizontally()
{
	if (!_controller)
		return;

	_controller->MoveHorizontally(this);
}

// Player's main function to interact with other actors and trigger their response to the interaction
bool Player::Interact(IInteractive* actor)
{
	if (StateMain::_state != State::REGULAR)
		return false;

	if (!actor)
		return false;

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A))
	{
		if (StateMain::_state != State::REGULAR)
			return false;

		/*if (dynamic_cast<Actor*>(actor)->_SInteract)
			CSimpleSound::GetInstance().PlaySound(dynamic_cast<Actor*>(actor)->_SInteract, 0);*/

		actor->Interact();

		if (dynamic_cast<IDialogue*>(actor))
			StateMain::SetState(State::DIALOGUE);

		return true;
	}
	return false;
}

// Player's main function to interact with other actors (collectable) and trigger their response to the interaction
bool Player::Interact(Collectable* collectable)
{
	if (StateMain::_state != State::REGULAR)
		return false;

	if (!collectable)
		return false;

	if (_interactSprite)
	{
		_interactSprite->SetPosition(GetPosition()->_x, GetPosition()->_y + 32);
		_interactSprite->Draw();
	}

	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A))
	{
		// The collectable is meant to be stored in a dedicated bag (decided with the collectable ID)
		for (auto i = 0; i < _inventory->_bags[collectable->_ID].second.size(); ++i)
		{
			// Looking for the first empty slot
			if (!_inventory->_bags[collectable->_ID].second[i])
			{
				// Stock the collected object in an empty bag slot
				_inventory->_bags[collectable->_ID].second[i] = collectable;
				collectable->OnCollected();
				std::cout << collectable->GetName() << " added in bag " << collectable->_ID << " at slot " << i << std::endl;
				// Removing the actor from the current scene as it is being itemized
				StateMain::_currentScene->RemoveActor(collectable);
				/*CSimpleSound::GetInstance().PlaySound(collectable->_SInteract, 0, -2500);*/
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
	auto actors{ StateMain::_currentScene->GetActors() };

	if (actors.size() <= 0)
		return;

	std::vector<Actor*> interactiveActors{};

	// Select all Collectable or Interactive actors
	for (auto& actor : actors)
		if (dynamic_cast<ICollectable*>(actor) || dynamic_cast<IInteractive*>(actor) || actor->GetMobility() == Mobility::MOVABLE)
			interactiveActors.emplace_back(actor);

	if (interactiveActors.size() <= 0)
		return;

	float ms{ GetMovementSpeed() };

	if (GetDirection() == Direction::LEFT || GetDirection() == Direction::DOWN)
		ms = -GetMovementSpeed();

	float x{ GetPosition()->_x };
	float y{ GetPosition()->_y };

	if (GetDirection() == Direction::RIGHT || GetDirection() == Direction::LEFT)
		x = GetPosition()->_x + ms;
	else
		y = GetPosition()->_y + ms;

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

	auto m = dynamic_cast<Character*>(closestActor);
	if (m)
	{	
		m->SetDirection(_direction);
		m->MoveHorizontally();
		m->MoveVertically();
		m->SetDirection(Direction::STILL);
		return;
	}
}

void Player::PlayDialogue()
{
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
	if (!stateDialogue)
		return;

	if (_currentDialogue.empty())
		stateDialogue->_currentDialogue = "[" + GetName() + "] says : ...";
	else
		stateDialogue->_currentDialogue = "[" + GetName() + "] says : " + _currentDialogue;
}