#include "../stdafx.h"
#include "Hall.h"

Hall::Hall(int ID, std::vector<Actor*> actors, CandlePuzzle* candlePuzzle) : Scene(ID, actors), _candlePuzzle{std::move(candlePuzzle)}
{
}


Hall::Hall(int ID, CandlePuzzle* candlePuzzle) : Scene(ID), _candlePuzzle{std::move(_candlePuzzle)}
{
}

Hall::~Hall()
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
bool Hall::Init()
{
	// Init only once
	if (Scene::Init())
		return true;

	/*Initiating Puzzles*/
	_candlePuzzle = new CandlePuzzle(CandlePuzzle::Status::PENDING);

	/*Triggers*/

	TriggerScene* entranceTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, WALL_OFFSET + TRIGGER_OFFSET), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET), new Collision(32, 32, Collision::ColliderType::Overlap), _SScene) };
	
	TriggerScene* loungeTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, MIDDLE_HEIGHT), new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET, MIDDLE_HEIGHT), new Collision(32, 32, Collision::ColliderType::Overlap), _WScene) };
	
	TriggerScene* libraryTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET, MIDDLE_HEIGHT),  new Collision(32, 32, Collision::ColliderType::Overlap), _EScene) };
	
	TriggerScene* roomTrigger{ new TriggerScene(MStairs.name, App::CreateSprite(MStairs.model, 1, 1, MStairs.frame, MStairs.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - WALL_OFFSET), new Vector2D(MIDDLE_WIDTH, WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET), new Collision(32, 32, Collision::ColliderType::Overlap), _NScene) };
	
	/*Initiating Props */

	auto carpet{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale), new Vector2D(512, 384), new Collision(64, 64, Collision::ColliderType::Overlap)) };
	
	std::vector<Vector2D*> v{ new Vector2D(514,466), new Vector2D(446,432), new Vector2D(580,432), new Vector2D(460,356), new Vector2D(564,356) };
	for (int i = 0; i < v.size(); ++i)
	{
		_candles.emplace_back(new Candle(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame, MCandle.scale), v[i], new Collision(10, 10)));
		_candles[i]->_SInteract = SFX.item_pick;
				_candlePuzzle->GetCandles().emplace_back(_candles[i]);
	}

	auto pentagramme{ new Actor(MPentagramme.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, 3), new Vector2D(516, 418), new Collision(48, 32, Collision::ColliderType::Overlap)) };
	
	auto bed{ new Actor(MBed.name, App::CreateSprite(MBed.model, 1, 1, MBed.frame, MBed.scale), new Vector2D(312, 464), new Collision(48, 32)) };
	
	auto smith{ new NPC("Ms. Smith", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), new Vector2D(512, 394), new Collision(32, 32)) };
		smith->dialogues.insert(std::make_pair(0, "You must not.. lighten your path.. the false angel.. shall be your doom ..!"));
	smith->SetCurrentDialogue(0);

	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, MCharlotte.frame, MCharlotte.scale), new Vector2D(300, 300), new Collision(32, 32)) };
		charlotte->dialogues.insert(std::make_pair(0, "A page from my journal must be around.. But it's so dark here ! Well, it always has been... You did it ! Serves her right once again, good bye Ms. Smith !"));
	charlotte->dialogues.insert(std::make_pair(1, "You did it ! Serves her right once again, good bye Ms. Smith !"));
	charlotte->SetCurrentDialogue(0);

	auto pillar{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), new Vector2D(MIDDLE_WIDTH - 70, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(32, 16)) };
	
	auto pillar2{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), new Vector2D(MIDDLE_WIDTH + 70, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(32, 16)) };
	
	auto railing{ new Actor(MRailing.name, App::CreateSprite(MRailing.model, 1, 1, MRailing.frame, MRailing.scale), new Vector2D(MIDDLE_WIDTH - 40, APP_VIRTUAL_HEIGHT - WALL_OFFSET), new Collision(32, 16)) };
	
	auto railing2{ new Actor(MRailing.name, App::CreateSprite(MRailing.model, 1, 1, MRailing.frame, MRailing.scale), new Vector2D(MIDDLE_WIDTH + 40, APP_VIRTUAL_HEIGHT - WALL_OFFSET), new Collision(32, 16)) };
	
	auto picture{ new Actor(MPicture.name, App::CreateSprite(MPicture.model, 1, 1, MPicture.frame, MPicture.scale), new Vector2D(MIDDLE_WIDTH - 150, APP_VIRTUAL_HEIGHT - WALL_OFFSET + TRIGGER_OFFSET), new Collision(32, 32)) };
	
	auto picture2{ new Actor(MPicture.name, App::CreateSprite(MPicture.model2, 1, 1, MPicture.frame, MPicture.scale), new Vector2D(MIDDLE_WIDTH + 150, APP_VIRTUAL_HEIGHT - WALL_OFFSET + TRIGGER_OFFSET), new Collision(32, 32)) };
	
	auto table{ new Actor(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), new Vector2D(WALL_OFFSET + 64, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(32, 32)) };
	
	auto commode{ new Actor(MCommode.name, App::CreateSprite(MCommode.model, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(WALL_OFFSET + 128, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(16, 32)) };
	
	ObjectController* objectC{ new ObjectController() };
	Character* candle{new Character(MCandle.name, App::CreateSprite(MCandle.model, 1, 2), new Vector2D(150, 200), new Collision(10, 10), 0, 6, objectC) };
	candle->SetDirection(Direction::RIGHT);
	
	/*Start Puzzle*/
	_candlePuzzle->StartPuzzle();

	return false;
}

void Hall::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Hall::Render()
{
	Scene::Render();
}

bool Hall::IsRoomCleared()
{
	if (!_candlePuzzle)
		return false;

	if (!_candlePuzzle->IsCleared())
		return false;

	else if (_candlePuzzle->_status == Puzzle::Status::CLEARED)
		return true;

	else if (_candlePuzzle->_status == Puzzle::Status::PENDING)
	{
		std::string description{ "\n[Page 1] :\n\nDear diary,\nToday's the same day as always.\nOur governess, Ms. Smith, scolded me all day for not behaving like a \"proper english lady\" or so she says..\nIt is always : \"Charlotte ! do not do this !\" or \"No.. Charlotte ! do not say this, say that instead !\", it is so frustrating !\nBut why is Edward bypassing everything when he behaves like a pig !? It is so unfair..\nWell, as we say : \"Birds of a feather flock together\" hehe !\nOh ! Ms. Pig better not read this or she is going to grunt with her pig nose wiiiiide open hehe !\nIn all seriousness, I hope Father and Mother will dismiss her very soon.. Or I'll do it myself ! Yes !\n\n- Charlotte Neville." };

		auto page{ new Page(MPage.name + " 1", App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(512, 394), new Collision(16, 16), 0, description) };
		
		auto it{ std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Ms. Smith"; }) };
		if (it != _actors.end())
		{
			RemoveActor(*it);
		}

		auto npc{ std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == "Charlotte Neville"; }) };
		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}
		_candlePuzzle->_status = Puzzle::Status::CLEARED;

		return true;
	}

	return false;
}


