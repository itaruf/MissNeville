#include "stdafx.h"
#include "ObjectController.h"

ObjectController::ObjectController()
{
}

ObjectController::~ObjectController()
{
}

void ObjectController::MoveHorizontally(Character* actor)
{
	if (actor->GetDirection() == Direction::RIGHT)
	{
		std::cout << actor->GetName() << std::endl;
		// Setting up the data to match the RIGHT direction
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_RIGHT);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->GetCollider()->isColliding(actor, other, actor->GetPosition()->_x +actor->GetMovementSpeed(), actor->GetPosition()->_y))
				if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x +actor->GetMovementSpeed(), actor->GetPosition()->_y);
	}

	else if (actor->GetDirection() == Direction::LEFT)
	{
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_LEFT);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->GetCollider()->isColliding(actor, other, actor->GetPosition()->_x -actor->GetMovementSpeed(), actor->GetPosition()->_y))
				if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x -actor->GetMovementSpeed(), actor->GetPosition()->_y);
	}
}

void ObjectController::MoveVertically(Character* actor)
{
	// Setting up the data to match the FORWARDS direction
	if (actor->GetDirection() == Direction::UP)
	{
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_FORWARDS);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			// Preventing the player to collide with themselves
			if (other == actor)
				continue;
			// if the player is about to collide with an actor, then the player doesn't move
			if (actor->GetCollider()->isColliding(actor, other, actor->GetPosition()->_x, actor->GetPosition()->_y + actor->GetMovementSpeed()))
				if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x, actor->GetPosition()->_y + actor->GetMovementSpeed());

	}

	else if (actor->GetDirection() == Direction::DOWN)
	{
		// Setting up the data to match the BACKWARDS direction
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_BACKWARDS);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->GetCollider()->isColliding(actor, other, actor->GetPosition()->_x, actor->GetPosition()->_y - actor->GetMovementSpeed()))
				if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x, actor->GetPosition()->_y - actor->GetMovementSpeed());
	}
}
