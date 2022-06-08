#include "stdafx.h"
#include "Hall.h"

Hall::Hall(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Hall::Hall(int ID) : Scene(ID)
{
}

Hall::~Hall()
{
}

void Hall::Init()
{
}

void Hall::Update(float deltaTime)
{
}

void Hall::Render()
{
}

bool Hall::IsRoomCleared()
{
	return false;
}
