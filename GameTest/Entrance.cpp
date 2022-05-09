#include "stdafx.h"
#include "Entrance.h"

Entrance::Entrance(int ID, std::vector<Actor*> actors, CandleEnigme* candleEnigme) : Room(ID, actors), candleEnigme{std::move(candleEnigme)}
{
}

Entrance::Entrance(int ID, Actor* actor, CandleEnigme* candleEnigme) : Room(ID, actor), candleEnigme{ std::move(candleEnigme)}
{
}

Entrance::Entrance(int ID, CandleEnigme* candleEnigme) : Room(ID), candleEnigme{std::move(candleEnigme)}
{
}

void Entrance::Init()
{
	/*Background First*/
	/*for (int j = 1; j < APP_VIRTUAL_HEIGHT / 64; j++)
	{ 
		for (int i = 1; i < APP_VIRTUAL_WIDTH / 64; i++)
		{
			auto item = new Item("Wood Plank", App::CreateSprite(".\\TestData\\wood-plank3.bmp", 1, 1), new Vector2D(0 + i * 64, 0 + j * 64), new Collision(Collision::ColliderType::Overlap, 64, 64), this);
			item->GetSprite()->SetFrame(1);
			item->GetSprite()->SetScale(0.5);
			actors.emplace_back(item);
		}
	}*/

	for (int i = 0; i < 3; i++) 
	{
		candles.emplace_back(new Candle("Candle " +std::to_string(i) , App::CreateSprite(".\\TestData\\candle.bmp", 1, 2), new Vector2D(200+i*32, 200), new Collision(Collision::ColliderType::Block, 10, 10), this));
		candles[i]->GetSprite()->SetFrame(0);
		candles[i]->GetSprite()->SetScale(0.5);

		// actors contain all the actors to collide or not with
		actors.emplace_back(candles.at(i)); 
	}

	auto bear = new Item("Bear", App::CreateSprite(".\\TestData\\bear.bmp", 1, 1), new Vector2D(512, 512), new Collision(Collision::ColliderType::Overlap, 32, 32), this);
	actors.emplace_back(bear);
	bear->GetSprite()->SetFrame(0);
	bear->GetSprite()->SetScale(0.25);

	/*auto clock = new Item("Clock", App::CreateSprite(".\\TestData\\broken-glasses-blood.bmp", 5, 4), new Vector2D(128, 128), new Collision(Collision::ColliderType::Overlap, 32, 32), this);
	clock->GetSprite()->SetFrame(4);
	clock->GetSprite()->SetScale(4);
	actors.emplace_back(clock);*/

	auto chair = new Item("Chair", App::CreateSprite(".\\TestData\\Maru's MV Bits.bmp", 16, 10), new Vector2D(128, 128), new Collision(Collision::ColliderType::Block, 16, 16, new Vector2D(0, 10)), this);
	chair->GetSprite()->SetFrame(1);
	chair->GetSprite()->SetScale(1);
	actors.emplace_back(chair);
}

void Entrance::Update(float deltaTime)
{
	for each (const auto & candle in candles)
	{
		candle->GetSprite()->Update(deltaTime);
	}
}

void Entrance::Render()
{
	for each (const auto& candle in candles)
	{
		candle->GetSprite()->Draw();
		candle->GetCollider()->DrawCollision(candle, 1, 1, 1);
	}
}
