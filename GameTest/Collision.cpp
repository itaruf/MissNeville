#include "stdafx.h"
#include "Collision.h"

Collision::Collision(ColliderType colliderType, float height, float width)
	: colliderType{ colliderType }, height{ height }, width{ width }
{
}

// https://levelup.gitconnected.com/2d-collision-detection-8e50b6b8b5c0
bool Collision::isColliding(Actor* character, Actor*& other, float x, float y)
{
	if (x - width < other->GetPosition().x + other->GetCollider()->GetWidth() &&
		x + width > other->GetPosition().x - other->GetCollider()->GetWidth() &&
		y - height < other->GetPosition().y + other->GetCollider()->GetHeight() &&
		y + height > other->GetPosition().y - other->GetCollider()->GetHeight())
		return true;
	return false;
}


const float& Collision::GetHeight() const
{
	return height;
}

void Collision::SetHeight(float value)
{
	height = value;
}

const float& Collision::GetWidth() const
{
	return width;
}

void Collision::SetWidth(float value)
{
	width = value;
}

void Collision::DrawCollision(Actor* actor, float r, float g, float b)
{
	// Middle Lines
	/*App::DrawLine(
		actor->GetPosition().x - width,
		actor->GetPosition().y,
		actor->GetPosition().x + width,
		actor->GetPosition().y,
		r, g, b);

	App::DrawLine(
		actor->GetPosition().x,
		actor->GetPosition().y - height,
		actor->GetPosition().x,
		actor->GetPosition().y + height,
		r, g, b);*/

	// Upper Bound
	App::DrawLine(
		actor->GetPosition().x - width, 
		actor->GetPosition().y + height, 
		actor->GetPosition().x + width, 
		actor->GetPosition().y + height,
		r, g, b);

	// Bottom Bound
	App::DrawLine(
		actor->GetPosition().x - width, 
		actor->GetPosition().y - height,
		actor->GetPosition().x + width, 
		actor->GetPosition().y - height,
		r, g, b);

	// Left Bound
	App::DrawLine(
		actor->GetPosition().x - width, 
		actor->GetPosition().y - height, 
		actor->GetPosition().x - width, 
		actor->GetPosition().y + height, 
		r, g, b);

	// Right Bound
	App::DrawLine(
		actor->GetPosition().x + width, 
		actor->GetPosition().y - height, 
		actor->GetPosition().x + width, 
		actor->GetPosition().y + height, 
		r, g, b);
}