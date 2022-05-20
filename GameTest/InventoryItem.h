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
	std::string description;

	InventoryItem(Usability usability, int ID, std::string& description);
	virtual ~InventoryItem();

	virtual bool UseItem();
};

