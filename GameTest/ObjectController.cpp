#include "../stdafx.h"
#include "ObjectController.h"

ObjectController::ObjectController(bool activated) : Controller(activated)
{
}

void ObjectController::MoveHorizontally(Character* actor)
{
	if (!_activated)
		return;

	float x{ actor->GetPosition().x }, y{ actor->GetPosition().y };
	Direction nextDir{ actor->_direction };
	if (actor->GetDirection() == Direction::RIGHT)
	{
		nextDir = Direction::LEFT;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_RIGHT);
		x = actor->GetPosition().x + actor->GetMovementSpeed();
		y = actor->GetPosition().y;
	}
	else if (actor->GetDirection() == Direction::LEFT)
	{
		nextDir = Direction::RIGHT;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_LEFT);
		x = actor->GetPosition().x - actor->GetMovementSpeed();
		y = actor->GetPosition().y;
	}

	if (actor->GetCollider()->_colliderType == ColliderType::Block)
	{
		for (const auto& other : StateController::_currentScene->GetActors())
		{
			if (other == actor)
				continue;

			if (actor->GetCollider()->isColliding(actor, other, x, y))
			{
				if (other->GetCollider()->_colliderType == ColliderType::Block)
				{
					if (other->GetTag() == "wall")
					{
						onChangeDirection();
						actor->_direction = nextDir;
					}
					return;
				}
			}
			else
			{
				actor->GetSprite()->SetPosition(x, y);
			}
		}
	}

	// ColliderType::Overlap
	else
	{
		for (const auto& other : StateController::_currentScene->GetActors())
		{
			if (other == actor)
				continue;

			if (actor->GetCollider()->isOverlapping(actor, other))
			{
				if (other->GetTag() == "wall")
				{
					onChangeDirection();
					actor->_direction = nextDir;
				}
			}
			actor->GetSprite()->SetPosition(x, y);
		}
	}
}

void ObjectController::MoveVertically(Character* actor)
{
	if (!_activated)
		return;

	float x{ actor->GetPosition().x}, y{ actor->GetPosition().y };
	Direction nextDir{ actor->_direction };
	if (actor->GetDirection() == Direction::UP)
	{
		nextDir = Direction::DOWN;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_FORWARDS);
		x = actor->GetPosition().x;
		y = actor->GetPosition().y + actor->GetMovementSpeed();
	}
	else if (actor->GetDirection() == Direction::DOWN)
	{
		nextDir = Direction::UP;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_BACKWARDS);
		x = actor->GetPosition().x;
		y = actor->GetPosition().y - actor->GetMovementSpeed();
	}

	if (actor->GetCollider()->_colliderType == ColliderType::Block)
	{
		for (const auto& other : StateController::_currentScene->GetActors())
		{
			if (other == actor)
				continue;

			if (actor->GetCollider()->isColliding(actor, other, x, y))
			{
				if (other->GetCollider()->_colliderType == ColliderType::Block)
				{
					if (other->GetTag() == "wall")
					{
						onChangeDirection();
						actor->_direction = nextDir;
					}
					return;
				}
			}
			else
			{
				actor->GetSprite()->SetPosition(x, y);
			}
		}
	}
	// ColliderType::Overlap
	else
	{
		for (const auto& other : StateController::_currentScene->GetActors())
		{
			if (other == actor)
				continue;

			if (actor->GetCollider()->isOverlapping(actor, other))
			{
				if (other->GetTag() == "wall")
				{
					onChangeDirection();
					actor->_direction = nextDir;
				}
			}
			actor->GetSprite()->SetPosition(x, y);
		}
	}
}