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
	_player->OpenBag(0);
	_currentSlot = 0;
}

void StateInventory::Exit()
{
	_currentSlot = 0;
	_player->CloseBag(0);
}

void StateInventory::Update()
{
	// Navigation in the bag
	Navigation();
}

void StateInventory::Render()
{
	Select();

	auto bag = _player->_inventory->_bags[0];
	
	float x = 800;
	float y = 400;

	float widthOff = 10;
	float width = 35;
	float height = 35;
	float heightOff = 50;

	size_t size = bag.second.size();

	for (int i = 0; i < size; ++i)
	{
		if (i == _currentSlot)
		{
			selected.r = 1;
			selected.g = 0;
			selected.b = 0;
		}
		else
		{
			selected.r = 1;
			selected.g = 1;
			selected.b = 1;
		}
		if (i % 3 == 0)
		{
			y -= heightOff;
			x = 800;
		}

		// Upper line
		App::DrawLine(
			x,
			y,
			x + width,
			y,
			selected.r, selected.g, selected.b);

		// Left Line
		App::DrawLine(
			x,
			y,
			x,
			y - height,
			selected.r, selected.g, selected.b);

		// Right Line
		App::DrawLine(
			x + width,
			y,
			x + width,
			y - height,
			selected.r, selected.g, selected.b);

		// Down line
		App::DrawLine(
			x,
			y - height,
			x + width,
			y - height,
			selected.r, selected.g, selected.b);

		//App::Print(((x + widthOff) + (x + width * widthOff)) / 2, ((y - heightOff + widthOff) + (y - heightOff + height * widthOff)) / 2, "Test");

		if (bag.second[i])
		{
			bag.second[i]->SetPosition((x + (x + width)) / 2,  (y + (y - height)) / 2);
			bag.second[i]->GetSprite()->Draw();
		}

		x = x + width + widthOff;
	}
}

void StateInventory::Navigation()
{
	_player->_inventory->_bags[0];

	// Right navigation
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
	{
		// We already are at the end of the bag
		if (_currentSlot >= _player->_inventory->GetNbSlotBag() - 1)
			return;

		_currentSlot++;
	}

	// Left navigation
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
	{
		// We already are at the beginning of the bag
		if (_currentSlot <= 0)
			return;

		_currentSlot--;
	}

	/*std::cout << _currentSlot << std::endl;*/
}

void StateInventory::Select()
{
	auto bag = _player->_inventory->_bags[0];

	if (!bag.second[_currentSlot])
	{
		/*std::cout << "slot " << _currentSlot << " is empty" << std::endl;*/
		App::Print(800, 370, GetChar(_currentSlot).c_str());
		/*App::Print(250, 250, "TEST");*/
		return;
	}

	/*std::cout << "slot " << _currentSlot << " " << bag.second[_currentSlot]->GetName() << std::endl;*/
	App::Print(800, 370, bag.second[_currentSlot]->GetName().c_str());
	/*App::Print(250, 250, "TEST");*/

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		bag.second[_currentSlot]->UseItem();
	}
}
