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
	if (initialized)
		return true;

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(LOUNGE_WALL_OFFSET, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LOUNGE_WALL_OFFSET, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, LOUNGE_WALL_OFFSET), new Collision(2, MIDDLE_WIDTH + LOUNGE_WALL_OFFSET * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET), new Collision(2, MIDDLE_WIDTH + LOUNGE_WALL_OFFSET * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LOUNGE_WALL_OFFSET, 2)) };
	wallRight->SetTag("wall");


	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET, MIDDLE_HEIGHT), new Collision(32, 32, Collision::ColliderType::Overlap), _EScene) };
	
	initialized = !initialized;
	return true;
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
