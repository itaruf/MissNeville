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

bool Hall::Init()
{
	if (Scene::Init())
		return true;

	// Triggers
	TriggerScene* entranceTrigger = new TriggerScene("Entrance Trigger", App::CreateSprite(".\\TestData\\Icons\\question-mark.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH / 2, WALL_OFFSET + TRIGGER_OFFSET), new Collision(Collision::ColliderType::Overlap, 16, 16), _SScene, new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT  - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET));
	entranceTrigger->GetSprite()->SetFrame(2);
	entranceTrigger->GetSprite()->SetScale(1);
	AddActor(entranceTrigger);

	return false;
}

void Hall::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Hall::Render()
{
	Scene::Render();
}

bool Hall::IsRoomCleared()
{
	return false;
}
