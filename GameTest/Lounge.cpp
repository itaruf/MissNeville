#include "../stdafx.h"
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

bool Lounge::Init()
{
	if (Scene::Init())
		return true;

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2), new Collision(16, 16, Collision::ColliderType::Overlap), _EScene, new Vector2D(WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET, APP_VIRTUAL_HEIGHT / 2)) };
	AddActor(hallTrigger);

	return false;
}

void Lounge::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Lounge::Render()
{
	Scene::Render();
}

bool Lounge::IsRoomCleared()
{
	return false;
}
