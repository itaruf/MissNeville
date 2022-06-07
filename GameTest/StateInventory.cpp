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
	auto player = GameState::_player;
	auto bag = player->_inventory->_bags[0];
	
	float x = 700;
	float y = 300;

	float widthOff = 25;
	float width = 4;
	float height = 3;
	float heightOff = 50;
	size_t size = bag.second.size();

	for (int i = 0; i < size; ++i)
	{
		if (i % 3 == 0)
		{
			y -= heightOff;
			x = 700;
			widthOff = 15;
		}

		// Upper line
		App::DrawLine(
			x + widthOff,
			y,
			x + width * widthOff,
			y,
			1, 1, 1);

		// Left Line
		App::DrawLine(
			x + widthOff,
			y - heightOff + widthOff,
			x + widthOff,
			y - heightOff + height * widthOff,
			1, 1, 1);

		// Right Line
		App::DrawLine(
			x + width * widthOff,
			y - heightOff + widthOff,
			x + width * widthOff,
			y - heightOff + height * widthOff,
			1, 1, 1);

		// Down line
		App::DrawLine(
			x + widthOff,
			y - heightOff + widthOff,
			x + width * widthOff,
			y - heightOff + widthOff,
			1, 1, 1);

		//App::Print(((x + widthOff) + (x + width * widthOff)) / 2, ((y - heightOff + widthOff) + (y - heightOff + height * widthOff)) / 2, "Test");

		if (bag.second[i])
		{
			bag.second[i]->SetPosition(((x + widthOff) + (x + width * widthOff)) / 2, ((y - heightOff + widthOff) + (y - heightOff + height * widthOff) / 2));
			bag.second[i]->GetSprite()->Draw();
		}

		x = x + width * widthOff;
	}
}

void StateInventory::Exit()
{
}
