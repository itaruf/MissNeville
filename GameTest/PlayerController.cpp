#include "stdafx.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::MoveHorizontally(Character* actor)
{
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT) || App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		// Setting up the data to match the RIGHT direction
		actor->SetDirection(Direction::RIGHT);
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_RIGHT);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->GetCollider()->isColliding(actor, other, actor->GetPosition()->_x + actor->GetMovementSpeed(), actor->GetPosition()->_y))
				if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x + actor->GetMovementSpeed(), actor->GetPosition()->_y);
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		// Setting up the data to match the LEFT direction
		actor->SetDirection(Direction::LEFT);
		actor->GetSprite()->SetAnimation(actor->GetSprite()->ANIM_LEFT);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->GetCollider()->isColliding(actor, other, actor->GetPosition()->_x - actor->GetMovementSpeed(), actor->GetPosition()->_y))
				if (other->GetCollider()->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x - actor->GetMovementSpeed(), actor->GetPosition()->_y);
	}
}

void PlayerController::MoveVertically(Character* actor)
{
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		// Setting up the data to match the FORWARDS direction
		actor->SetDirection(Direction::UP);
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
		// else the player can move
		actor->GetSprite()->SetPosition(actor->GetPosition()->_x, actor->GetPosition()->_y + actor->GetMovementSpeed());
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		// Setting up the data to match the BACKWARDS direction
		actor->SetDirection(Direction::DOWN);
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
