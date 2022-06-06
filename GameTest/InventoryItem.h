#pragma once

#ifndef INVENTORYITEM_H_
#define INVENTORYITEM_H_

// Class which represents the item version of an actor
class InventoryItem
{
private:
protected:
public:
	// Defines if the item of an inventory is usable or not
	enum class Usability
	{
		Usable,
		Unusable,
	};

	Usability _usability;
	int _ID;
	std::string _description;

	InventoryItem(Usability usability, int ID, std::string& description);
	virtual ~InventoryItem();

	// Each item will have its own treatment
	virtual bool UseItem();
};

#endif
