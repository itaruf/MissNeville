#include "../stdafx.h"
#include "Room.h"

Room::Room(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Room::Room(int ID) : Scene(ID)
{
}

Room::~Room()
{
}

bool Room::Init()
{
	if (Scene::Init())
		return true;

	TriggerScene* hallTrigger = new TriggerScene(MTriggerScene.name, App::CreateSprite(MCommode.model2, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(APP_VIRTUAL_WIDTH / 2, WALL_OFFSET + TRIGGER_OFFSET), new Collision(16, 16, Collision::ColliderType::Overlap), _SScene, new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET));
	AddActor(hallTrigger);

	return false;
}

void Room::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Room::Render()
{
	Scene::Render();
}

bool Room::IsRoomCleared()
{
	return false;
}
