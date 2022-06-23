#include "../stdafx.h"
#include "Lounge.h"

Lounge::Lounge(int ID) : Scene(ID)
{
}

Lounge::~Lounge()
{
}

void Lounge::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);

	/*std::cout << StateMain::_player->GetPosition()->_x << std::endl;*/

	ObjectController* objectC{new ObjectController() };

	StateMain::_player->SetPosition(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET - 128, MIDDLE_HEIGHT);

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(LOUNGE_WALL_OFFSET, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LOUNGE_WALL_OFFSET, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, LOUNGE_WALL_OFFSET), new Collision(2, MIDDLE_WIDTH + LOUNGE_WALL_OFFSET * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET), new Collision(2, MIDDLE_WIDTH + LOUNGE_WALL_OFFSET * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LOUNGE_WALL_OFFSET, 2)) };
	wallRight->SetTag("wall");


	/*Weapons*/
	auto weapon{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET - 128, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 32), new Collision(16, 16), 0, 2, objectC) };
	weapon->SetTag("lethal");
	weapon->SetDirection(Direction::DOWN);

	/*auto weapon2{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 4, MKnife.frame, MKnife.scale), new Vector2D(MIDDLE_WIDTH - LOUNGE_WALL_OFFSET, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 32), new Collision(16, 16), 0, 2, objectC) };
	weapon->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_AXE, 1 / 15.0f, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, true);
	weapon2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_AXE);
	weapon2->SetTag("lethal");
	weapon2->SetDirection(Direction::UP);

	auto weapon3{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 4, MKnife.frame, MKnife.scale), new Vector2D(LOUNGE_WALL_OFFSET + 128, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 32), new Collision(16, 16), 0, 2, objectC) };
	weapon->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_AXE, 1 / 15.0f, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, true);
	weapon3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_AXE);
	weapon3->SetTag("lethal");
	weapon3->SetDirection(Direction::DOWN);*/

	auto oven{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(LOUNGE_WALL_OFFSET + 32, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 16), new Collision(92, 32)) };

	auto oven2{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 16), new Collision(92, 32)) };

	auto barrel{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET - 64, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 32), new Collision(32, 32)) };

	auto barrel2{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET - 64, APP_VIRTUAL_HEIGHT - LOUNGE_WALL_OFFSET - 32), new Collision(32, 32)) };

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL_OFFSET - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(LOUNGE_WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _EScene) };
	
	initialized = !initialized;
}

void Lounge::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Lounge::Render()
{
	Scene::Render();
}

void Lounge::Exit()
{
}

bool Lounge::IsRoomCleared()
{
	return false;
}
