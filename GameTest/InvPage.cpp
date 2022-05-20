#include "stdafx.h"
#include "InvPage.h"

InvPage::InvPage(Usability usability, int ID) : InventoryItem(usability, ID)
{
}

InvPage::~InvPage()
{
	printf("INVPAGE DESTRUCTOR CALLED\n");
}

bool InvPage::UseItem()
{
	return false;
}
