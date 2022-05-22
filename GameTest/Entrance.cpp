#include "stdafx.h"
#include "Entrance.h"

Entrance::Entrance(int ID, std::vector<Actor*> actors, std::shared_ptr<GameState>& gameState, CandleEnigme* candleEnigme) : Room(ID, actors, gameState), candleEnigme{std::move(candleEnigme)}
{
}

Entrance::Entrance(int ID, Actor* actor, std::shared_ptr<GameState>& gameState, CandleEnigme* candleEnigme) : Room(ID, actor, gameState), candleEnigme{ std::move(candleEnigme)}
{
}

Entrance::Entrance(int ID, std::shared_ptr<GameState>& gameState, CandleEnigme* candleEnigme) : Room(ID, gameState), candleEnigme{std::move(candleEnigme)}
{
}

Entrance::~Entrance()
{
	printf("ENTRANCE DESTRUCTOR CALLED\n");

	delete candleEnigme;
	candleEnigme = nullptr;
	
	/*for (auto& candle : candles)
	{
		if (candle)
			delete candle;
	}*/
	candles.clear();
}

void Entrance::Init()
{
	/*Background First*/
	/*for (int j = 3; j <= APP_VIRTUAL_HEIGHT / 64 - 3; j++)
	{ 
		for (int i = 3; i <= APP_VIRTUAL_WIDTH / 64 - 3; i++)
		{
			auto ground = new Actor("Wood Plank", App::CreateSprite(".\\TestData\\wood-plank3-b.bmp", 1, 1), new Vector2D(0 + i * 64, 0 + j * 64), new Collision(Collision::ColliderType::Overlap, 32, 32), this);
			ground->GetSprite()->SetFrame(1);
			ground->GetSprite()->SetScale(0.5);
			AddActor(ground);
		}
	}*/
	background = App::CreateSprite(".\\TestData\\Backgrouds\\night.bmp", 1, 1);
	background->SetScale(2.0f);
	background->SetAnimation(0);

	/*Initiating Enigmes*/
	candleEnigme = new CandleEnigme(CandleEnigme::Status::PENDING);

	/*Initiating Props */

	auto wall = new Actor("wall", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(64 * 2, APP_VIRTUAL_HEIGHT), new Collision(Collision::ColliderType::Block, APP_VIRTUAL_HEIGHT, 2), gameState->currentRoom);
	wall->GetSprite()->SetFrame(1);
	wall->GetSprite()->SetScale(3);

	AddActor(wall);

	auto wall2 = new Actor("wall2", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH, 64 * 2), new Collision(Collision::ColliderType::Block, 2, APP_VIRTUAL_WIDTH), gameState->currentRoom);
	wall2->GetSprite()->SetFrame(1);
	wall2->GetSprite()->SetScale(3);
	AddActor(wall2);

	auto wall3 = new Actor("wall3", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT - 64 * 2), new Collision(Collision::ColliderType::Block, 2, APP_VIRTUAL_WIDTH), gameState->currentRoom);
	wall3->GetSprite()->SetFrame(1);
	wall3->GetSprite()->SetScale(3);
	AddActor(wall3);

	auto wall4 = new Actor("wall4", App::CreateSprite(".\\TestData\\.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH - 64 * 2, APP_VIRTUAL_HEIGHT - 64 * 2), new Collision(Collision::ColliderType::Block, APP_VIRTUAL_HEIGHT, 2), gameState->currentRoom);
	wall4->GetSprite()->SetFrame(1);
	wall4->GetSprite()->SetScale(3);
	AddActor(wall4);

	auto carpet = new Actor("Carpet", App::CreateSprite(".\\TestData\\Props\\carpet-b.bmp", 1, 1), new Vector2D(512, 384), new Collision(Collision::ColliderType::Overlap, 64, 64), gameState->currentRoom);
	carpet->GetSprite()->SetFrame(1);
	carpet->GetSprite()->SetScale(3);
	AddActor(carpet);

	std::vector<Vector2D*> v{ new Vector2D(514,466), new Vector2D(446,432), new Vector2D(580,432), new Vector2D(460,356), new Vector2D(564,356) };
	for (int i = 0; i < v.size(); ++i)
	{
		candles.emplace_back(new Candle("Candle " + std::to_string(i), App::CreateSprite(".\\TestData\\Props\\candle.bmp", 1, 2), v[i], new Collision(Collision::ColliderType::Block, 10, 10), gameState->currentRoom));
		candles[i]->GetSprite()->SetFrame(0);
		candles[i]->GetSprite()->SetScale(0.5);
		AddActor(candles.at(i));
		candleEnigme->GetCandles().emplace_back(candles[i]);
	}

	auto pentagramme = new Actor("Pentagramme", App::CreateSprite(".\\TestData\\Props\\pentagramme.bmp", 4, 4), new Vector2D(516, 418), new Collision(Collision::ColliderType::Overlap, 48, 32), gameState->currentRoom);
	pentagramme->GetSprite()->SetFrame(0);
	pentagramme->GetSprite()->SetScale(3);
	AddActor(pentagramme);

	auto bed = new Actor("Bed", App::CreateSprite(".\\TestData\\Props\\bed-blue-b.bmp", 1, 1), new Vector2D(312, 464), new Collision(Collision::ColliderType::Block, 48, 32), gameState->currentRoom);
	bed->GetSprite()->SetFrame(0);
	bed->GetSprite()->SetScale(2);
	AddActor(bed);

	auto charlotte = new NPC("Charlotte", App::CreateSprite(".\\TestData\\Characters\\charlotte.bmp", 3, 4), new Vector2D(724, 464), new Collision(Collision::ColliderType::Block, 32, 32), gameState->currentRoom, 0, 0);
	charlotte->GetSprite()->SetFrame(1);
	charlotte->GetSprite()->SetScale(3);
	AddActor(charlotte);
	charlotte->dialogues.insert(std::make_pair(0, std::make_pair(false, "A page from my journal should be around.. But it's so dark here ! Well, it always has been...")));

	auto sprite  = new Actor("Question", App::CreateSprite(".\\TestData\\Icons\\question-mark.bmp", 1, 1), new Vector2D(724, 518), new Collision(Collision::ColliderType::Overlap, 0, 0), gameState->currentRoom);
	sprite->GetSprite()->SetFrame(0);
	sprite->GetSprite()->SetScale(2);
	AddActor(sprite);


	/*Add this room to the collection of rooms*/
	gameState.get()->rooms.emplace_back(this);

	/*Start Enigme*/
	candleEnigme->StartEnigme();
}

void Entrance::Update(float deltaTime)
{
	Room::Update(deltaTime);

	for (const auto & candle : candles)
	{
		if (!candle)
			candle->GetSprite()->Update(deltaTime);
	}

	for (const auto& item : actors)
	{
		if (item)
			item->GetSprite()->Update(deltaTime);
	}

	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER, true))
	{
		std::string description = "Page 2";
		auto page = new Page("Page", App::CreateSprite(".\\TestData\\Tiles-Props-pack\\page.bmp", 1, 1), new Vector2D(512, 394), new Collision(Collision::ColliderType::Block, 16, 16), gameState->currentRoom, new InventoryItem(InventoryItem::Usability::Usable, 0, description), 0);
		page->GetSprite()->SetFrame(0);
		page->GetSprite()->SetScale(4);
		AddActor(page);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		std::string description = "Page 3";
		auto page = new Page("Page", App::CreateSprite(".\\TestData\\Tiles-Props-pack\\page.bmp", 1, 1), new Vector2D(512, 394), new Collision(Collision::ColliderType::Block, 16, 16), gameState->currentRoom, new InventoryItem(InventoryItem::Usability::Usable, 0, description), 0);
		page->GetSprite()->SetFrame(0);
		page->GetSprite()->SetScale(4);
		AddActor(page);
	}*/
}

void Entrance::Render()
{
	for (const auto& candle : candles)
	{
		if (!candle)
		{
			candle->GetSprite()->Draw();
			candle->GetCollider()->DrawCollision(candle, 1, 1, 1);
		}
	}

	for (const auto& item : actors)
	{
		if (item)
		{
			item->GetSprite()->Draw();
			item->GetCollider()->DrawCollision(item, 50, 50, 50);
		}
	}
}

bool Entrance::IsRoomCleared()
{
	if (candleEnigme) 
	{
		if (candleEnigme->IsCleared())
		{
			if (candleEnigme->status == Enigme::Status::PENDING)
			{
				std::string description = "Page 1";
				auto page = new Page("Page", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(512, 394), new Collision(Collision::ColliderType::Block, 16, 16), gameState->currentRoom, new InventoryItem(InventoryItem::Usability::Usable, 0, description), 0);
				page->GetSprite()->SetFrame(0);
				page->GetSprite()->SetScale(4);
				AddActor(page);

				candleEnigme->status = Enigme::Status::CLEARED;
			}
			return true;
		}
	}
	return false;
}


