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

	auto wall = new Actor("wall", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(128, APP_VIRTUAL_HEIGHT), new Collision(Collision::ColliderType::Block, APP_VIRTUAL_HEIGHT, 2));
	wall->GetSprite()->SetFrame(1);
	wall->GetSprite()->SetScale(3);
	AddActor(wall);

	auto wall2 = new Actor("wall2", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH, 128), new Collision(Collision::ColliderType::Block, 2, APP_VIRTUAL_WIDTH));
	wall2->GetSprite()->SetFrame(1);
	wall2->GetSprite()->SetScale(3);
	AddActor(wall2);

	auto wall3 = new Actor("wall3", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT - 128), new Collision(Collision::ColliderType::Block, 2, APP_VIRTUAL_WIDTH));
	wall3->GetSprite()->SetFrame(1);
	wall3->GetSprite()->SetScale(3);
	AddActor(wall3);

	auto wall4 = new Actor("wall4", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH - 128, APP_VIRTUAL_HEIGHT - 128), new Collision(Collision::ColliderType::Block, APP_VIRTUAL_HEIGHT, 2));
	wall4->GetSprite()->SetFrame(1);
	wall4->GetSprite()->SetScale(3);
	AddActor(wall4);

	// Triggers
	TriggerScene* entranceTrigger = new TriggerScene("Entrance Trigger", App::CreateSprite(".\\TestData\\Props\\carpet-b.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH / 2, 128 + 24), new Collision(Collision::ColliderType::Overlap, 16, 16));
	entranceTrigger->GetSprite()->SetFrame(1);
	entranceTrigger->GetSprite()->SetScale(1);
	AddActor(entranceTrigger);
	entranceTrigger->_scene = _SScene;

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
