#include "../stdafx.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::MoveHorizontally(Character* actor)
{
	float x{ actor->_position->_x }, y{ actor->_position->_y };
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT) || App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		// Setting up the data to match the RIGHT direction
		actor->_direction = Direction::RIGHT;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_RIGHT);
		x = actor->_position->_x + actor->_movementSpeed;
		y = actor->_position->_y;
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		// Setting up the data to match the LEFT direction
		actor->_direction = Direction::LEFT;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_LEFT);
		x = actor->_position->_x - actor->_movementSpeed;
		y = actor->_position->_y;
	}

	for (const auto& other : GameState::_currentScene->GetActors())
	{
		if (other == actor)
			continue;
		if (actor->_collider->isColliding(actor, other, x, y))
		{
			if (other->_collider->_colliderType == Collision::ColliderType::Block)
				return;
		}		
	}

	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT) || App::GetController().GetLeftThumbStickX() > 0.5f 
		|| App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) || App::GetController().GetLeftThumbStickX() < -0.5f)
		actor->_sprite->SetPosition(x, y);
}

void PlayerController::MoveVertically(Character* actor)
{
	float x{ actor->_position->_x }, y{ actor->_position->_y };
	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		// Setting up the data to match the UP direction
		actor->_direction = Direction::UP;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_FORWARDS);
		x = actor->_position->_x;
		y = actor->_position->_y + actor->_movementSpeed;
	}

	else if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		// Setting up the data to match the DOWN direction
		actor->_direction = Direction::DOWN;
		actor->_sprite->SetAnimation(actor->_sprite->ANIM_BACKWARDS);
		x = actor->_position->_x;
		y = actor->_position->_y - actor->_movementSpeed;
	}

	for (const auto& other : GameState::_currentScene->GetActors())
	{
		if (other == actor)
			continue;
		if (actor->_collider->isColliding(actor, other, x, y))
		{
			if (other->_collider->_colliderType == Collision::ColliderType::Block)
				return;
		}
	}

	if (App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) || App::GetController().GetLeftThumbStickY() > 0.5f 
		|| App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN) || App::GetController().GetLeftThumbStickY() < -0.5f)
		actor->_sprite->SetPosition(x, y);
}