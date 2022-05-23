#include "stdafx.h"
#include "InvPage.h"

InvPage::InvPage(Usability usability, int ID, std::string& description) : InventoryItem(usability, ID, description)
{
}

InvPage::~InvPage()
{
	printf("INVPAGE DESTRUCTOR CALLED\n");
}

// WIP 
bool InvPage::UseItem()
{
	return false;
}
