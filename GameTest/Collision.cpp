#include "stdafx.h"
#include "Collision.h"

Collision::Collision(ColliderType colliderType, float height, float width, Vector2D* offset)
	: colliderType{ colliderType }, height{ height }, width{ width }, offset{std::move(offset)}
{
}

Collision::~Collision()
{
	if (offset)
		delete offset;
}

bool Collision::isColliding(Actor* actor, Actor* other, float x, float y)
{
	if (x + offset->x - width < other->GetPosition()->x + other->GetCollider()->offset->x + other->GetCollider()->GetWidth() &&
		x + offset->x + width > other->GetPosition()->x + other->GetCollider()->offset->x - other->GetCollider()->GetWidth() &&
		y + offset->y - height < other->GetPosition()->y + other->GetCollider()->offset->y + other->GetCollider()->GetHeight() &&
		y + offset->y + height > other->GetPosition()->y + other->GetCollider()->offset->y - other->GetCollider()->GetHeight())
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
	if (!actor)
		return;

	if (colliderType == ColliderType::Overlap)
	{
		actor = nullptr;
		return;
	}

	// Middle Lines
	/*App::DrawLine(
		actor->GetPosition()->x - width,
		actor->GetPosition()->y,
		actor->GetPosition()->x + width,
		actor->GetPosition()->y,
		r, g, b);

	App::DrawLine(
		actor->GetPosition()->x,
		actor->GetPosition()->y - height,
		actor->GetPosition()->x,
		actor->GetPosition()->y + height,
		r, g, b);*/

	// Upper Bound
	App::DrawLine(
		actor->GetPosition()->x + actor->GetCollider()->offset->x - width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y + height,
		actor->GetPosition()->x + actor->GetCollider()->offset->x + width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y + height,
		r, g, b);

	// Bottom Bound
	App::DrawLine(
		actor->GetPosition()->x + actor->GetCollider()->offset->x - width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y - height,
		actor->GetPosition()->x + actor->GetCollider()->offset->x + width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y - height,
		r, g, b);

	// Left Bound
	App::DrawLine(
		actor->GetPosition()->x + actor->GetCollider()->offset->x - width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y - height,
		actor->GetPosition()->x + actor->GetCollider()->offset->x - width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y + height,
		r, g, b);

	// Right Bound
	App::DrawLine(
		actor->GetPosition()->x + actor->GetCollider()->offset->x + width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y - height,
		actor->GetPosition()->x + actor->GetCollider()->offset->x + width,
		actor->GetPosition()->y + actor->GetCollider()->offset->y + height,
		r, g, b);

	actor = nullptr;
}

Vector2D* Collision::GetDownLeftColPos(Actor* actor)
{
	auto v{ new Vector2D(actor->GetPosition()->x + offset->x - width, actor->GetPosition()->y + offset->y - height) };
	actor = nullptr;
	return v;
}

Vector2D* Collision::GetDownRightColPos(Actor* actor)
{
	auto v{ new Vector2D(actor->GetPosition()->x + offset->x + width, actor->GetPosition()->y + offset->y - height) };
	actor = nullptr;
	return v;

}

Vector2D* Collision::GetUpLeftColPos(Actor* actor)
{
	auto v{ new Vector2D(actor->GetPosition()->x + offset->x - width, actor->GetPosition()->y + offset->y + height) };
	actor = nullptr;
	return v;
}

Vector2D* Collision::GetUpRightColPos(Actor* actor)
{
	auto v{ new Vector2D(actor->GetPosition()->x + offset->x + width, actor->GetPosition()->y + offset->y + height) };
	actor = nullptr;
	return v;
}
