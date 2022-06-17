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

	startingPos = new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2 - 128);

	StateMain::_player->SetPosition(startingPos);

	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2), new Collision(16, 16, Collision::ColliderType::Overlap), _WScene, new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET, APP_VIRTUAL_HEIGHT / 2)) };
	AddActor(hallTrigger);

	auto wallH2{ new Actor(MWall.name, App::CreateSprite(MTable.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT - 364), new Collision(2, APP_VIRTUAL_WIDTH)) };
	wallH2->SetTag("wall");
	AddActor(wallH2);

	auto wallV2{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(WALL_OFFSET + 256, APP_VIRTUAL_HEIGHT / 4), new Collision(APP_VIRTUAL_HEIGHT / 4, 2)) };
	wallV2->SetTag("wall");
	AddActor(wallV2);

	auto wallV3{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(wallV2->GetPosition()->_x + 256, APP_VIRTUAL_HEIGHT / 4), new Collision(APP_VIRTUAL_HEIGHT / 4, 2)) };
	wallV2->SetTag("wall");
	AddActor(wallV3);

	auto wallV4{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(wallV2->GetPosition()->_x + 128, APP_VIRTUAL_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT / 2, 2)) };
	wallV2->SetTag("wall");
	AddActor(wallV4);

	// First Part
	TriggerScene* tp1{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 100), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos)};
	AddActor(tp1);

	TriggerScene* tp2{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 200), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, new Vector2D(wallV4->GetPosition()->_x + 128,  wallH2->GetPosition()->_y + 200)) };
	AddActor(tp2);

	// Second Part
	TriggerScene* tp3{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV4->GetPosition()->_x + 256,  wallH2->GetPosition()->_y + 200), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET, APP_VIRTUAL_HEIGHT / 2)) };
	AddActor(tp3);

	TriggerScene* tp4{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV4->GetPosition()->_x + 256,  wallH2->GetPosition()->_y + 100), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos) };
	AddActor(tp4);

	TriggerScene* tp5{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV4->GetPosition()->_x + 128,  wallH2->GetPosition()->_y + 100), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos) };
	AddActor(tp5);

	// Third Part
	TriggerScene* tp6{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV3->GetPosition()->_x + 128,  wallH2->GetPosition()->_y - 100), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos) };
	AddActor(tp6);

	TriggerScene* tp7{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV3->GetPosition()->_x + 128,  wallH2->GetPosition()->_y - 200), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y + 100)) };
	AddActor(tp7);

	// Fourth Part
	TriggerScene* tp8{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y + 200), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos) };
	AddActor(tp8);

	TriggerScene* tp9{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x , wallH2->GetPosition()->_y + 200), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, new Vector2D(APP_VIRTUAL_WIDTH / 2 , APP_VIRTUAL_HEIGHT / 2 - 64)) };
	AddActor(tp9);

	TriggerScene* tp10{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x , wallH2->GetPosition()->_y + 100), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos) };
	AddActor(tp10);

	// Fifth Part 
	TriggerScene* tp11{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH / 2 , APP_VIRTUAL_HEIGHT / 2 - 128), new Collision(16, 16, Collision::ColliderType::Overlap), nullptr, startingPos)};
	AddActor(tp11);

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
