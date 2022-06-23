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
	StateMain::_player->GetSprite()->SetPosition(MIDDLE_WIDTH, ENTRANCE_WALL + 64);

	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - ENTRANCE_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(ENTRANCE_WIDTH_WALL + 16 + i * 32, HALL_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(ENTRANCE_WIDTH_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - ENTRANCE_WALL * 2, 2)) };
	wallLeft->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - ENTRANCE_WALL * 2, 2)) };
	wallRight->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL), new Collision(2, APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL), new Collision(2, APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL * 2)) };
	wallTop->SetTag("wall");

	/*PROPS*/

	auto carpet{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), new Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL + 48), new Collision(64, 64, ColliderType::Overlap)) };
	auto carpet2{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), new Vector2D(MIDDLE_WIDTH, carpet->GetPosition()->_y	+ 92), new Collision(64, 64, ColliderType::Overlap)) };
	auto carpet3{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), new Vector2D(MIDDLE_WIDTH, carpet2->GetPosition()->_y + 92), new Collision(64, 64, ColliderType::Overlap)) };
	auto carpet4{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), new Vector2D(MIDDLE_WIDTH, carpet3->GetPosition()->_y + 92), new Collision(64, 64, ColliderType::Overlap)) };

	auto pillar{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), new Vector2D(MIDDLE_WIDTH - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL), new Collision(32, 16)) };
	auto pillar2{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), new Vector2D(MIDDLE_WIDTH + 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL), new Collision(32, 16)) };

	auto candle{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, ENTRANCE_WALL + 40), new Collision(30, 10)) };
	auto candle2{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, candle->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle3{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, candle2->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle4{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, candle3->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle5{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, candle4->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle6{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, candle5->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle7{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH - 48, candle6->GetPosition()->_y + 48), new Collision(30, 10)) };

	auto candle8{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, ENTRANCE_WALL + 40), new Collision(30, 10)) };
	auto candle9{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, candle8->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle10{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, candle9->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle11{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, candle10->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle12{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, candle11->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle13{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, candle12->GetPosition()->_y + 48), new Collision(30, 10)) };
	auto candle14{ new Actor(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame2, MCandle.scale), new Vector2D(MIDDLE_WIDTH + 48, candle13->GetPosition()->_y + 48), new Collision(30, 10)) };

	auto web{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(ENTRANCE_WIDTH_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 80), new Collision(32, 32, ColliderType::Overlap))};
	auto web2{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web3{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(ENTRANCE_WIDTH_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 144), new Collision(32, 32, ColliderType::Overlap)) };
	auto web4{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 176), new Collision(32, 32, ColliderType::Overlap)) };
	auto web5{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(ENTRANCE_WIDTH_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 208), new Collision(32, 32, ColliderType::Overlap)) };
	auto web6{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 240), new Collision(32, 32, ColliderType::Overlap)) };
	auto web7{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(ENTRANCE_WIDTH_WALL + 16, ENTRANCE_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto web8{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 16, ENTRANCE_WALL + 48), new Collision(32, 32, ColliderType::Overlap)) };

	auto picture{ new Actor(MPicture.name, App::CreateSprite(MPicture.model, 1, 1, MPicture.frame, MPicture.scale), new Vector2D(MIDDLE_WIDTH - 112, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 32), new Collision(32, 32, ColliderType::Overlap)) };
	auto picture2{ new Actor(MPicture.name, App::CreateSprite(MPicture.model2, 1, 1, MPicture.frame, MPicture.scale), new Vector2D(MIDDLE_WIDTH + 112, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 32), new Collision(32, 32, ColliderType::Overlap)) };

	auto commode{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(ENTRANCE_WIDTH_WALL + 16, MIDDLE_HEIGHT + 64), new Collision(64, 32)) };
	auto commode2{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(APP_VIRTUAL_WIDTH -ENTRANCE_WIDTH_WALL - 16, MIDDLE_HEIGHT), new Collision(64, 32)) };
	auto commode3{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale4), new Vector2D(ENTRANCE_WIDTH_WALL + 8, MIDDLE_HEIGHT - 128), new Collision(64, 32)) };

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MTriggerScene.model, 2, 1, MTriggerScene.frame, MTriggerScene.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 16), new Vector2D(MIDDLE_WIDTH, HALL_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS), new Collision(32, 32, ColliderType::Overlap), _NScene, false) };
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
