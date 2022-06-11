﻿#include "stdafx.h"
#include "Entrance.h"

Entrance::Entrance(int ID, std::vector<Actor*> actors, CandlePuzzle* candlePuzzle) : Scene(ID, actors), _candlePuzzle{std::move(candlePuzzle)}
{
}


Entrance::Entrance(int ID, CandlePuzzle* candlePuzzle) : Scene(ID), _candlePuzzle{std::move(_candlePuzzle)}
{
}

Entrance::~Entrance()
{
	printf("ENTRANCE DESTRUCTOR CALLED\n");

	// Freeing all the memory allocated on the heap
	delete _candlePuzzle;
	
	/*for (auto& candle : _candles)
	{
		if (candle)
			delete candle;
	}*/
	_candles.clear();
}

// WIP - Initialization of the entrance scene 
bool Entrance::Init()
{
	// Init only once
	if (Scene::Init())
		return true;

	/*Background First*/
	/*for (int j = 3; j <= APP_VIRTUAL_HEIGHT / 64 - 3; j++)
	{ 
		for (int i = 3; i <= APP_VIRTUAL_WIDTH / 64 - 3; i++)
		{
			auto ground = new Actor("Wood Plank", App::CreateSprite(".\\TestData\\Backgrounds\\wood-plank3-b.bmp", 1, 1), new Vector2D(0 + i * 64, 0 + j * 64), new Collision(Collision::ColliderType::Overlap, 32, 32), this);
			ground->GetSprite()->SetFrame(1);
			ground->GetSprite()->SetScale(0.5);
			AddActor(ground);
		}
	}*/

	/*_background = App::CreateSprite(".\\TestData\\Backgrounds\\night.bmp", 1, 1);
	_background->SetScale(2.0f);
	_background->SetAnimation(0);*/

	/*Initiating Puzzles*/
	_candlePuzzle = new CandlePuzzle(CandlePuzzle::Status::PENDING);

	/*Initiating Props */

	auto carpet = new Actor("Carpet", App::CreateSprite(".\\TestData\\Props\\carpet-b.bmp", 1, 1), new Vector2D(512, 384), new Collision(Collision::ColliderType::Overlap, 64, 64));
	carpet->GetSprite()->SetFrame(1);
	carpet->GetSprite()->SetScale(3);
	AddActor(carpet);

	std::vector<Vector2D*> v{ new Vector2D(514,466), new Vector2D(446,432), new Vector2D(580,432), new Vector2D(460,356), new Vector2D(564,356) };
	for (int i = 0; i < v.size(); ++i)
	{
		_candles.emplace_back(new Candle("Candle " + std::to_string(i), App::CreateSprite(".\\TestData\\Props\\candle.bmp", 1, 2), v[i], new Collision(Collision::ColliderType::Block, 10, 10)));
		_candles[i]->GetSprite()->SetFrame(0);
		_candles[i]->GetSprite()->SetScale(0.5);
		AddActor(_candles.at(i));
		_candlePuzzle->GetCandles().emplace_back(_candles[i]);
	}

	auto pentagramme = new Actor("Pentagramme", App::CreateSprite(".\\TestData\\Props\\pentagramme.bmp", 4, 4), new Vector2D(516, 418), new Collision(Collision::ColliderType::Overlap, 48, 32));
	pentagramme->GetSprite()->SetFrame(0);
	pentagramme->GetSprite()->SetScale(3);
	AddActor(pentagramme);

	auto bed = new Actor("Bed", App::CreateSprite(".\\TestData\\Props\\bed-blue-b.bmp", 1, 1), new Vector2D(312, 464), new Collision(Collision::ColliderType::Block, 48, 32));
	bed->GetSprite()->SetFrame(0);
	bed->GetSprite()->SetScale(2);
	AddActor(bed);

	auto smith = new NPC("Ms. Smith", App::CreateSprite(".\\TestData\\Characters\\family.bmp", 3, 4), new Vector2D(512, 394), new Collision(Collision::ColliderType::Block, 16, 16), 0, 0);
	smith->GetSprite()->SetFrame(1);
	smith->GetSprite()->SetScale(3.5);
	AddActor(smith);
	smith->dialogues.insert(std::make_pair(0, std::make_pair(false, "You must not.. lighten your path.. the false angel.. shall be your doom ..!")));
	smith->SetCurrentDialogue(0);

	auto charlotte = new NPC("Charlotte Neville", App::CreateSprite(".\\TestData\\Characters\\charlotte.bmp", 3, 4), new Vector2D(300, 300), new Collision(Collision::ColliderType::Block, 16, 16), 0, 0);
	charlotte->GetSprite()->SetFrame(1);
	charlotte->GetSprite()->SetScale(3);
	AddActor(charlotte);
	charlotte->dialogues.insert(std::make_pair(0, std::make_pair(false, "A page from my journal should be around.. But it's so dark here ! Well, it always has been...")));
	charlotte->dialogues.insert(std::make_pair(1, std::make_pair(false, "You did it ! Serves her right once again, good bye Ms. Smith !")));
	charlotte->SetCurrentDialogue(0);

	/*TriggerScene* loungeTrigger = new TriggerScene("Lounge Trigger", App::CreateSprite(".\\TestData\\Icons\\question-mark.bmp", 1, 1), new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2), new Collision(Collision::ColliderType::Overlap, 16, 16), _WScene, new Vector2D());
	loungeTrigger->GetSprite()->SetFrame(1);
	loungeTrigger->GetSprite()->SetScale(2);
	AddActor(loungeTrigger);
	loungeTrigger->_scene = _WScene;*/

	TriggerScene* hallTrigger = new TriggerScene("Hall Trigger", App::CreateSprite(".\\TestData\\Icons\\question-mark.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(Collision::ColliderType::Overlap, 16, 16), _NScene, new Vector2D(APP_VIRTUAL_WIDTH / 2, WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET));
	hallTrigger->GetSprite()->SetFrame(1);
	hallTrigger->GetSprite()->SetScale(2);
	AddActor(hallTrigger);


	//Character* candle{new Character("Candle", App::CreateSprite(".\\TestData\\Props\\candle.bmp", 1, 2), new Vector2D(150, 150), new Collision(Collision::ColliderType::Block, 10, 10), 0, 2) };
	//candle->GetSprite()->SetFrame(0);
	//candle->GetSprite()->SetScale(1);
	//candle->SetDirection(Direction::RIGHT);
	//AddActor(candle);

	/*Start Puzzle*/
	_candlePuzzle->StartPuzzle();

	return false;
}

void Entrance::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		auto page = new Page("Page 1", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(300, 250), new Collision(Collision::ColliderType::Block, 8, 8), 0, "lul");
		page->GetSprite()->SetFrame(0);
		page->GetSprite()->SetScale(3);
		AddActor(page);
	}
}

void Entrance::Render()
{
	Scene::Render();
}

bool Entrance::IsRoomCleared()
{
	if (!_candlePuzzle)
		return false;

	if (!_candlePuzzle->IsCleared())
		return false;

	else if (_candlePuzzle->_status == Puzzle::Status::CLEARED)
		return true;

	else if (_candlePuzzle->_status == Puzzle::Status::PENDING)
	{
		std::string description = "\n[Page 1] :\n\nDear diary,\nToday's the same day as always.\nOur governess, Ms. Smith, scolded me all day for not behaving like a \"proper english lady\" or so she says..\nIt is always : \"Charlotte ! do not do this !\" or \"No.. Charlotte ! do not say this, say that instead !\", it is so frustrating !\nBut why is Edward bypassing everything when he behaves like a pig !? It is so unfair..\nWell, as we say : \"Birds of a feather flock together\" hehe !\nOh ! Ms. Pig better not read this or she is going to grunt with her pig nose wiiiiide open hehe !\nIn all seriousness, I hope Father and Mother will dismiss her very soon.. Or I'll do it myself ! Yes !\n\n- Charlotte Neville.";

		auto page = new Page("Page 1", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(512, 394), new Collision(Collision::ColliderType::Block, 8, 8), 0, description);
		page->GetSprite()->SetFrame(0);
		page->GetSprite()->SetScale(3);
		AddActor(page);

		auto it = std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Ms. Smith"; });
		if (it != _actors.end())
		{
			RemoveActor(*it);
		}

		auto npc = std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == "Charlotte"; });
		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}
		_candlePuzzle->_status = Puzzle::Status::CLEARED;

		return true;
	}

	return false;
}


