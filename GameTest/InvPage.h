#pragma once

#include "InventoryItem.h"

// Class which represents a page in the inventory
class InvPage : public InventoryItem
{
private:
protected:
public:
	InvPage(Usability usability, int ID, std::string& description);
	~InvPage();

	bool UseItem() override;
};

