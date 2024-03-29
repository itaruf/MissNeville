#include "../stdafx.h"
#include "Collision.h"

Collision::Collision() : Collision(32 / 2, 32 / 2, ColliderType::Block, Vector2D(0,0))
{
}

Collision::Collision(float height, float width, ColliderType colliderType, Vector2D offset)
	: _colliderType{ colliderType }, _height{ height / 2 }, _width{ width / 2 }, _offset{std::move(offset)}
{
}

Collision::~Collision()
{
}

// Check if an actor is colliding with another by projecting their future move
bool Collision::isColliding(Actor* actor, Actor* other, float x, float y)
{
	if (!actor || !other)
		return false;

	if (dynamic_cast<Collectable*>(other) && dynamic_cast<Collectable*>(other)->isItemized())
		return false;

	auto x1{ actor->GetPosition().x };
	auto y1{ actor->GetPosition().y };
	auto w1{ actor->GetCollider()->GetWidth() };
	auto h1{ actor->GetCollider()->GetHeight() };
	auto x1off{ actor->GetCollider()->_offset.x };
	auto y1off{ actor->GetCollider()->_offset.y };

	auto x2{ other->GetPosition().x };
	auto y2{ other->GetPosition().y };
	auto w2{ other->GetCollider()->GetWidth() };
	auto h2{ other->GetCollider()->GetHeight() };
	auto x2off{ other->GetCollider()->_offset.x };
	auto y2off{ other->GetCollider()->_offset.y };

	if (x + x1off - _width < x2 + x2off + w2 &&
		x + x1off + _width > x2 + x2off - w2 &&
		y + y1off - _height < y2 + y2off + h2 &&
		y + y1off + _height > y2 + y2off - h2)
		return true;

	return false;
}

bool Collision::isOverlapping(Actor* actor, Actor* other)
{
	if (!actor || !other)
		return false;

	if (dynamic_cast<Collectable*>(other) && dynamic_cast<Collectable*>(other)->isItemized())
		return false;

	auto x1{ actor->GetPosition().x };
	auto y1{ actor->GetPosition().y };
	auto w1{ actor->GetCollider()->GetWidth() };
	auto h1{ actor->GetCollider()->GetHeight() };
	auto x1off{ actor->GetCollider()->_offset.x};
	auto y1off{ actor->GetCollider()->_offset.y};

	auto x2{ other->GetPosition().x };
	auto y2{ other->GetPosition().y };
	auto w2{ other->GetCollider()->GetWidth() };
	auto h2{ other->GetCollider()->GetHeight() };
	auto x2off{ other->GetCollider()->_offset.x };
	auto y2off{ other->GetCollider()->_offset.y };

	if (x1 + x1off - _width < x2 + x2off + w2 &&
		x1 + x1off + _width > x2 + x2off - w2 &&
		y1 + y1off - _height < y2 + y2off + h2 &&
		y1 + y1off + _height > y2 + y2off - h2)
		return true;

	return false;
}

// Get the height of the collider
const float& Collision::GetHeight() const
{
	return _height;
}

// Set the height of the collider
void Collision::SetHeight(float value)
{
	_height = value;
}

// Get the width of the collider
const float& Collision::GetWidth() const
{
	return _width;
}

// Set the width of the collider
void Collision::SetWidth(float value)
{
	_width = value;
}

// DEBUG : Draw the collider with the actor pos in the center
void Collision::DrawCollision(Actor* actor, float r, float g, float b)
{
	return; // Print no collider

	if (!actor)
		return;

	/*if (_colliderType == ColliderType::Overlap)
		return;*/

	// Upper Bound
	App::DrawLine(
		actor->GetPosition().x + actor->GetCollider()->_offset.x - _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y + _height,
		actor->GetPosition().x + actor->GetCollider()->_offset.x + _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y + _height,
		r, g, b);

	// Bottom Bound
	App::DrawLine(
		actor->GetPosition().x + actor->GetCollider()->_offset.x - _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y - _height,
		actor->GetPosition().x + actor->GetCollider()->_offset.x + _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y - _height,
		r, g, b);

	// Left Bound
	App::DrawLine(
		actor->GetPosition().x + actor->GetCollider()->_offset.x - _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y - _height,
		actor->GetPosition().x + actor->GetCollider()->_offset.x - _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y + _height,
		r, g, b);

	// Right Bound
	App::DrawLine(
		actor->GetPosition().x + actor->GetCollider()->_offset.x + _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y - _height,
		actor->GetPosition().x + actor->GetCollider()->_offset.x + _width,
		actor->GetPosition().y + actor->GetCollider()->_offset.y + _height,
		r, g, b);
}