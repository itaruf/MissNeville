#include "stdafx.h"
#include "StateInventory.h"

StateInventory::StateInventory()
{
}

StateInventory::~StateInventory()
{
}

void StateInventory::Enter()
{
}

void StateInventory::Update()
{
}

void StateInventory::Render()
{
	auto bag = GameState::_player->_inventory->_bags[0];
	
	float x = 700;
	float y = 300;
	float offset = 15;
	size_t size = bag.second.size();

	for (int i = 0; i < size; ++i)
	{
		if (i % 3 == 0)
		{
			y -= 25;
			x = 700;
			offset = 15;
		}

		// Upper line
		App::DrawLine(
			x + offset,
			y,
			x + 3 * offset,
			y,
			1, 1, 1);

		// Left Line
		App::DrawLine(
			x + offset,
			y - 35 + offset,
			x + offset,
			y - 35 + 2 * offset,
			1, 1, 1);

		// Right Line
		App::DrawLine(
			x + 3 * offset,
			y - 35 + offset,
			x + 3 * offset,
			y - 35 + 2 * offset,
			1, 1, 1);

		// Down line
		App::DrawLine(
			x + offset,
			y - 35 + offset,
			x + 3 * offset,
			y - 35 + offset,
			1, 1, 1);

		x = x + 2 * offset;
	}
}

void StateInventory::Exit()
{
}
