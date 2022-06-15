#include "../stdafx.h"
#include "ObjectController.h"

ObjectController::ObjectController()
{
}

ObjectController::~ObjectController()
{
}

void ObjectController::MoveHorizontally(Character* actor)
{
	float x{ actor->GetPosition()->_x }, y{ actor->GetPosition()->_y };
	Direction nextDir{ actor->_direction };
	if (actor->GetDirection() == Direction::RIGHT)
	{
		nextDir = Direction::LEFT;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_RIGHT);
		x = actor->GetPosition()->_x + actor->GetMovementSpeed();
		y = actor->GetPosition()->_y;
	}
	else if (actor->GetDirection() == Direction::LEFT)
	{
		nextDir = Direction::RIGHT;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_LEFT);
		x = actor->GetPosition()->_x - actor->GetMovementSpeed();
		y = actor->GetPosition()->_y;
	}

	for (const auto& other : StateMain::_currentScene->GetActors())
	{
		if (other == actor)
			continue;

		if (actor->GetCollider()->isColliding(actor, other, x, y))
		{
			if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
			{
				if (other->GetTag() == "wall")
					actor->_direction = nextDir;
				return;
			}
		}
		else
		{
			actor->GetSprite()->SetPosition(x, y);
		}
	}
}

void ObjectController::MoveVertically(Character* actor)
{
	float x{ actor->GetPosition()->_x}, y{ actor->GetPosition()->_y };
	Direction nextDir{ actor->_direction };
	if (actor->GetDirection() == Direction::UP)
	{
		nextDir = Direction::DOWN;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_FORWARDS);
		x = actor->GetPosition()->_x;
		y = actor->GetPosition()->_y + actor->GetMovementSpeed();
	}
	else if (actor->GetDirection() == Direction::DOWN)
	{
		nextDir = Direction::UP;
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_BACKWARDS);
		x = actor->GetPosition()->_x;
		y = actor->GetPosition()->_y - actor->GetMovementSpeed();
	}

	for (const auto& other : StateMain::_currentScene->GetActors())
	{
		if (other == actor)
			continue;
		if (actor->GetCollider()->isColliding(actor, other, x, y))
		{
			if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
			{
				if (other->GetTag() == "wall")
					actor->_direction = nextDir;
				return;
			}
		}
		else
		{
			actor->GetSprite()->SetPosition(x, y);
		}
	}
}
