#include "stdafx.h"
#include "Collision.h"

Collision::Collision(ColliderType colliderType, float height, float width, Vector2D* offset)
	: _colliderType{ colliderType }, _height{ height }, _width{ width }, _offset{std::move(offset)}
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
	return; // Print no collider

	if (!actor)
		return;

	if (_colliderType == ColliderType::Overlap)
	{
		actor = nullptr;
		return;
	}

	// Middle Lines
	/*App::DrawLine(
		actor->GetPosition()->_x - _width,
		actor->GetPosition()->_y,
		actor->GetPosition()->_x + _width,
		actor->GetPosition()->_y,
		r, g, b);

	App::DrawLine(
		actor->GetPosition()->_x,
		actor->GetPosition()->_y - _height,
		actor->GetPosition()->_x,
		actor->GetPosition()->_y + _height,
		r, g, b);*/

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

	actor = nullptr;
}

//Vector2D* Collision::GetDownLeftColPos(Actor* actor)
//{
//	auto v{ new Vector2D(actor->GetPosition()->_x + _offset->_x - _width, actor->GetPosition()->_y + _offset->_y - _height) };
//	actor = nullptr;
//	return v;
//}
//
//Vector2D* Collision::GetDownRightColPos(Actor* actor)
//{
//	auto v{ new Vector2D(actor->GetPosition()->_x + _offset->_x + _width, actor->GetPosition()->_y + _offset->_y - _height) };
//	actor = nullptr;
//	return v;
//
//}
//
//Vector2D* Collision::GetUpLeftColPos(Actor* actor)
//{
//	auto v{ new Vector2D(actor->GetPosition()->_x + _offset->_x - _width, actor->GetPosition()->_y + _offset->_y + _height) };
//	actor = nullptr;
//	return v;
//}
//
//Vector2D* Collision::GetUpRightColPos(Actor* actor)
//{
//	auto v{ new Vector2D(actor->GetPosition()->_x + _offset->_x + _width, actor->GetPosition()->_y + _offset->_y + _height) };
//	actor = nullptr;
//	return v;
//}
