#include "../stdafx.h"
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
	if (Scene::Init())
		return true;

	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MCommode.model2, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2), new Collision(16, 16, Collision::ColliderType::Overlap), _WScene, new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET, APP_VIRTUAL_HEIGHT / 2)) };
	AddActor(hallTrigger);

	return false;
}

void Library::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Library::Render()
{
	Scene::Render();
}

bool Library::IsRoomCleared()
{
	return false;
}
