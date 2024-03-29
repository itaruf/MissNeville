#include "../stdafx.h"
#include "Collectable.h"

Collectable::Collectable(std::string name, CSimpleSprite* sprite, Vector2D position, Collision* collider, int ID, std::string description) : Actor(name, sprite, position, collider), _ID { ID }, _description{ std::move(description) }
{
}

Collectable::~Collectable()
{
}

int Collectable::GetID()
{
	return _ID;
}

bool Collectable::isItemized()
{
	return _itemized;
}

void Collectable::OnCollected()
{
	if (_SCollected)
		CSimpleSound::GetInstance().PlaySoundW(_SCollected, 0);

	onCollected();
	_itemized = true;
}

void Collectable::UseItem()
{
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(_description);
	StateController::SetState(State::DIALOGUE);
}