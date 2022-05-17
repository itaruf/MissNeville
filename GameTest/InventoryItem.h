#pragma once
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

	InventoryItem(Usability usability, int ID);
	virtual ~InventoryItem() = default;

	virtual bool UseItem();
};

