#include "stdafx.h"
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

	/*Initiating Puzzles*/
	_candlePuzzle = new CandlePuzzle(CandlePuzzle::Status::PENDING);

	/*Initiating Props */

	auto carpet = new Actor(MCarpet::name, App::CreateSprite(MCarpet::model, 1, 1, MCarpet::frame, MCarpet::scale), new Vector2D(512, 384), new Collision(64, 64, Collision::ColliderType::Overlap));
	AddActor(carpet);

	std::vector<Vector2D*> v{ new Vector2D(514,466), new Vector2D(446,432), new Vector2D(580,432), new Vector2D(460,356), new Vector2D(564,356) };
	for (int i = 0; i < v.size(); ++i)
	{
		_candles.emplace_back(new Candle(MCandle::name, App::CreateSprite(MCandle::model, 1, 2, MCandle::frame, MCandle::scale), v[i], new Collision(10, 10)));
		AddActor(_candles.at(i));
		_candlePuzzle->GetCandles().emplace_back(_candles[i]);
	}

	auto pentagramme = new Actor(MPentagramme::name, App::CreateSprite(MPentagramme::model, 4, 4, MPentagramme::frame, MPentagramme::scale), new Vector2D(516, 418), new Collision(48, 32, Collision::ColliderType::Overlap));
	AddActor(pentagramme);

	auto bed = new Actor(MBed::name, App::CreateSprite(MBed::model, 1, 1, MBed::frame, MBed::scale), new Vector2D(312, 464), new Collision(48, 32));
	AddActor(bed);

	auto smith = new NPC("Ms. Smith", App::CreateSprite(MFamily::model, 3, 4, MFamily::frame, MFamily::scale), new Vector2D(512, 394), new Collision(16, 16));
	AddActor(smith);
	smith->dialogues.insert(std::make_pair(0, std::make_pair(false, "You must not.. lighten your model.. the false angel.. shall be your doom ..!")));
	smith->SetCurrentDialogue(0);

	auto charlotte = new NPC(MCharlotte::name, App::CreateSprite(MCharlotte::model, 3, 4, MCharlotte::frame, MCharlotte::scale), new Vector2D(300, 300), new Collision(16, 16));
	AddActor(charlotte);
	charlotte->dialogues.insert(std::make_pair(0, std::make_pair(false, "A page from my journal should be around.. But it's so dark here ! Well, it always has been...")));
	charlotte->dialogues.insert(std::make_pair(1, std::make_pair(false, "You did it ! Serves her right once again, good bye Ms. Smith !")));
	charlotte->SetCurrentDialogue(0);

	TriggerScene* hallTrigger = new TriggerScene(MTriggerScene::name, App::CreateSprite(MCommode::model2, 1, 1, MCommode::frame, MCommode::scale), new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(16, 16, Collision::ColliderType::Overlap), _NScene, new Vector2D(APP_VIRTUAL_WIDTH / 2, WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET));
	AddActor(hallTrigger);

	ObjectController* objectC{ new ObjectController() };
	Character* candle{new Character(MCandle::name, App::CreateSprite(MCandle::model, 1, 2), new Vector2D(150, 200), new Collision(10, 10), 0, 6, objectC) };
	candle->SetDirection(Direction::RIGHT);
	AddActor(candle);

	/*Start Puzzle*/
	_candlePuzzle->StartPuzzle();

	return false;
}

void Entrance::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		auto page = new Page("Page 1", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(300, 250), new Collision(8, 8), 0, "lul");
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
		std::string description = "\n[Page 1] :\n\nDear diary,\nToday's the same day as always.\nOur governess, Ms. Smith, scolded me all day for not behaving like a \"proper english lady\" or so she says..\nIt is always : \"MCharlotte ! do not do this !\" or \"No.. MCharlotte ! do not say this, say that instead !\", it is so frustrating !\nBut why is Edward bypassing everything when he behaves like a pig !? It is so unfair..\nWell, as we say : \"Birds of a feather flock together\" hehe !\nOh ! Ms. Pig better not read this or she is going to grunt with her pig nose wiiiiide open hehe !\nIn all seriousness, I hope Father and Mother will dismiss her very soon.. Or I'll do it myself ! Yes !\n\n- MCharlotte Neville.";

		auto page = new Page("Page 1", App::CreateSprite(MPage::model, 1, 1, MPage::frame, MPage::scale), new Vector2D(512, 394), new Collision(8, 8), 0, description);
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


