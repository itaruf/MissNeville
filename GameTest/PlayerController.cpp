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
		actor->_direction = Direction::RIGHT;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_RIGHT);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->_collider->isColliding(actor, other, actor->_position->_x + actor->_movementSpeed, actor->_position->_y))
				if (other->_collider->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->_sprite->SetPosition(actor->_position->_x + actor->_movementSpeed, actor->_position->_y);
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		// Setting up the data to match the LEFT direction
		actor->_direction = Direction::LEFT;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_LEFT);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->_collider->isColliding(actor, other, actor->_position->_x - actor->_movementSpeed, actor->_position->_y))
				if (other->_collider->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->_sprite->SetPosition(actor->_position->_x - actor->_movementSpeed, actor->_position->_y);
	}
}

void PlayerController::MoveVertically(Character* actor)
{

	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		// Setting up the data to match the FORWARDS direction
		actor->_direction = Direction::UP;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_FORWARDS);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			// Preventing the player to collide with themselves
			if (other == actor)
				continue;
			// if the player is about to collide with an actor, then the player doesn't move
			if (actor->_collider->isColliding(actor, other, actor->_position->_x, actor->_position->_y + actor->_movementSpeed))
				if (other->_collider->_colliderType == Collision::ColliderType::Block)
					return;
		}
		// else the player can move
		actor->_sprite->SetPosition(actor->_position->_x, actor->_position->_y + actor->_movementSpeed);
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		// Setting up the data to match the BACKWARDS direction
		actor->_direction = Direction::DOWN;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_BACKWARDS);
		for (const auto& other : GameState::_currentScene->GetActors())
		{
			if (other == actor)
				continue;
			if (actor->_collider->isColliding(actor, other, actor->_position->_x, actor->_position->_y - actor->_movementSpeed))
				if (other->_collider->_colliderType == Collision::ColliderType::Block)
					return;
		}
		actor->_sprite->SetPosition(actor->_position->_x, actor->_position->_y - actor->_movementSpeed);
	}
}
