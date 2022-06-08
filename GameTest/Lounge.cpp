#include "stdafx.h"
#include "Lounge.h"

Lounge::Lounge(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Lounge::Lounge(int ID) : Scene(ID)
{
}

Lounge::~Lounge()
{
}

void Lounge::Init()
{
}

void Lounge::Update(float deltaTime)
{
}

void Lounge::Render()
{
}

bool Lounge::IsRoomCleared()
{
	return false;
}
