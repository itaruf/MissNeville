#include "../stdafx.h"
#include "Entrance.h"

Entrance::Entrance(int ID) : Scene(ID)
{
}

Entrance::~Entrance()
{
}

void Entrance::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);
	StateMain::_player->SetPosition(MIDDLE_WIDTH, ENTRANCE_WALL_OFFSET + 64);

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(ENTRANCE_WALL_OFFSET, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + ENTRANCE_WALL_OFFSET, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL_OFFSET), new Collision(2, MIDDLE_WIDTH + ENTRANCE_WALL_OFFSET * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL_OFFSET), new Collision(2, MIDDLE_WIDTH + ENTRANCE_WALL_OFFSET * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WALL_OFFSET, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + ENTRANCE_WALL_OFFSET, 2)) };
	wallRight->SetTag("wall");

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MTriggerScene.model, 2, 1, MTriggerScene.frame, MTriggerScene.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL_OFFSET - TRIGGER_OFFSET), new Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET), new Collision(32, 32, ColliderType::Overlap), _NScene) };
}

void Entrance::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Entrance::Render()
{
	Scene::Render();
}

void Entrance::Exit()
{
}

bool Entrance::IsRoomCleared()
{
	return true;
}
