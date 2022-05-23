#pragma once

#ifndef INVENTORYITEM_H_
#define INVENTORYITEM_H_

class InventoryItem
{
private:
protected:
public:
	enum class Usability
	{
		Usable,
		Unusable,
	};

	Usability usability;
	int ID;
	std::string description;

	InventoryItem(Usability usability, int ID, std::string& description);
	virtual ~InventoryItem();

	// Each item will have its own treatment
	virtual bool UseItem();
};

#endif
