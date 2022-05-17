#pragma once

#include "InventoryItem.h"

class InvPage : public InventoryItem
{
private:
protected:
public:
	InvPage(Usability usability, int ID);
	~InvPage();

	bool UseItem() override;
};

