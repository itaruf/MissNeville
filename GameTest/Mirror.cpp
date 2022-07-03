#include "../stdafx.h"
#include "Mirror.h"

Mirror::Mirror(std::string name, CSimpleSprite* sprite, Vector2D* position, Collision* collider) : Actor(name, sprite, position, collider)
{
	_SInteract = SFX.mirror_broken;
}

Mirror::~Mirror()
{
}

bool Mirror::isRepaired()
{
	return _repaired;
}

void Mirror::Interact()
{
	if (_repaired)
	{
		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };

		if (!stateDialogue)
			return;

		_onInteract();

		stateDialogue->_currentDialogue.emplace_back(DDetective.r4);
		StateController::SetState(State::DIALOGUE);
		return;
	}

	auto p{ StateController::_player };
	if (!p)
		return;

	if (!p->_inventory)
		return;

	auto bag{ p->_inventory->_bags[0].second };

	// Looking for all mirror shards in the player's bag
	if (GetCollectedMirrorShards() < nbShards)
	{
		CSimpleSound::GetInstance().PlaySoundW(_SInteract, 0);
		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };

		if (!stateDialogue)
			return;
		
		_onInteract();

		stateDialogue->_currentDialogue.emplace_back(DDetective.r2);
		StateController::SetState(State::DIALOGUE);
		return;
	}
	
	for (auto& item : bag)
	{
		auto mshard{ dynamic_cast<MirrorShard*>(item) };
		if (!mshard)
			continue;

		_onRepaired();

		p->_inventory->RemoveItem(mshard);
	}

	// the mirror is repaired
	CSimpleSound::GetInstance().PlaySoundW(_SMirror_repaired, 0);
	_repaired = true;
	_sprite->SetFrame(0);
}

int Mirror::GetCollectedMirrorShards()
{
	auto bag{ StateController::_player->_inventory->_bags[0].second };

	int nb{ 0 };

	// Looking for all mirror shards in the player's bag
	for (auto& item : bag)
	{
		auto mshard{ dynamic_cast<MirrorShard*>(item) };
		if (!mshard)
			continue;
		nb++;
	}

	return nb;
}
