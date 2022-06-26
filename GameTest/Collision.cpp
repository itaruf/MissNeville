#include "../stdafx.h"
#include "Collision.h"
#include "Collectable.h"

Collision::Collision() : Collision(32 / 2, 32 / 2, ColliderType::Block, new Vector2D())
{
}

Collision::Collision(float height, float width, ColliderType colliderType, Vector2D* offset)
	: _colliderType{ colliderType }, _height{ height / 2 }, _width{ width / 2 }, _offset{std::move(offset)}
{
}

Collision::~Collision()
{
	/*printf("COLLISION DESTRUCTOR CALLED\n");*/

	if (_offset)
		delete _offset;
}

// Check if an actor is colliding with another by projecting their future move
bool Collision::isColliding(Actor* actor, Actor* other, float x, float y)
{
	if (!actor || !other)
		return false;

	if (dynamic_cast<Collectable*>(other) && dynamic_cast<Collectable*>(other)->itemized)
		return false;

	auto x1{ actor->GetPosition()->_x };
	auto y1{ actor->GetPosition()->_y };
	auto w1{ actor->GetCollider()->GetWidth() };
	auto h1{ actor->GetCollider()->GetHeight() };
	auto x1off{ actor->GetCollider()->_offset->_x };
	auto y1off{ actor->GetCollider()->_offset->_y };

	auto x2{ other->GetPosition()->_x };
	auto y2{ other->GetPosition()->_y };
	auto w2{ other->GetCollider()->GetWidth() };
	auto h2{ other->GetCollider()->GetHeight() };
	auto x2off{ other->GetCollider()->_offset->_x };
	auto y2off{ other->GetCollider()->_offset->_y };

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

	if (dynamic_cast<Collectable*>(other) && dynamic_cast<Collectable*>(other)->itemized)
		return false;

	auto x1{ actor->GetPosition()->_x };
	auto y1{ actor->GetPosition()->_y };
	auto w1{ actor->GetCollider()->GetWidth() };
	auto h1{ actor->GetCollider()->GetHeight() };
	auto x1off{ actor->GetCollider()->_offset->_x};
	auto y1off{ actor->GetCollider()->_offset->_y};

	auto x2{ other->GetPosition()->_x };
	auto y2{ other->GetPosition()->_y };
	auto w2{ other->GetCollider()->GetWidth() };
	auto h2{ other->GetCollider()->GetHeight() };
	auto x2off{ other->GetCollider()->_offset->_x };
	auto y2off{ other->GetCollider()->_offset->_y };

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
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x - _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y + _height,
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x + _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y + _height,
		r, g, b);

	// Bottom Bound
	App::DrawLine(
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x - _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y - _height,
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x + _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y - _height,
		r, g, b);

	// Left Bound
	App::DrawLine(
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x - _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y - _height,
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x - _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y + _height,
		r, g, b);

	// Right Bound
	App::DrawLine(
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x + _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y - _height,
		actor->GetPosition()->_x + actor->GetCollider()->_offset->_x + _width,
		actor->GetPosition()->_y + actor->GetCollider()->_offset->_y + _height,
		r, g, b);
}