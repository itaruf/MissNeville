#pragma once

#include "InventoryItem.h"

class InvPage : public InventoryItem
{
private:
protected:
public:
	InvPage(Usability usability, int ID, std::string& description);
	~InvPage();

	bool UseItem() override;
};

