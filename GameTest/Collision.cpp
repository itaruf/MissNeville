#include "../stdafx.h"
#include "Collision.h"
#include "Collectable.h"

Collision::Collision() : _colliderType{ ColliderType::Block }, _height{32 / 2}, _width{ 32 / 2 }, _offset{ new Vector2D()}
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

	if (x + _offset->_x - _width < other->GetPosition()->_x + other->GetCollider()->_offset->_x + other->GetCollider()->GetWidth() &&
		x + _offset->_x + _width > other->GetPosition()->_x + other->GetCollider()->_offset->_x - other->GetCollider()->GetWidth() &&
		y + _offset->_y - _height < other->GetPosition()->_y + other->GetCollider()->_offset->_y + other->GetCollider()->GetHeight() &&
		y + _offset->_y + _height > other->GetPosition()->_y + other->GetCollider()->_offset->_y - other->GetCollider()->GetHeight())
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
	//return; // Print no collider

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