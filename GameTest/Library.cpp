#include "stdafx.h"
#include "Library.h"

Library::Library(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Library::Library(int ID) : Scene(ID)
{
}

Library::~Library()
{
}

bool Library::Init()
{
	return true;
}

void Library::Update(float deltaTime)
{
}

void Library::Render()
{
}

bool Library::IsRoomCleared()
{
	return false;
}
