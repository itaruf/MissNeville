#include "stdafx.h"
#include "InvPage.h"

InvPage::InvPage(Usability usability, int ID) : InventoryItem(usability, ID)
{
}

InvPage::~InvPage()
{
}

bool InvPage::UseItem()
{
	return false;
}
