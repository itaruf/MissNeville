#include "../stdafx.h"
#include "Hall.h"

Hall::Hall(int ID) : Scene(ID)
{
}

Hall::Hall(int ID, CandlePuzzle* puzzle) : Scene(ID), _candlePuzzle(puzzle)
{
}

Hall::~Hall()
{
	delete _candlePuzzle;
	
	/*for (auto& candle : _candles)
	{
		if (candle)
			delete candle;
	}*/
	_candles.clear();
}

void Hall::Init()
{
	// Init only once
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateController::_player);

	/*Background First*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - HALL_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - HALL_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), Vector2D(HALL_WALL + 16 + i * 32, HALL_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(HALL_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - HALL_WALL * 2, 2)) };
	wallLeft->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - HALL_WALL * 2, 2)) };
	wallRight->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, HALL_WALL), new Collision(2, APP_VIRTUAL_WIDTH - HALL_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL), new Collision(2, APP_VIRTUAL_WIDTH - HALL_WALL * 2)) };
	wallTop->SetTag("wall");

	/*Triggers*/

	TriggerScene* entranceTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, 0.8), Vector2D(MIDDLE_WIDTH, HALL_WALL + TRIGGER_OFFSET), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS - 32), new Collision(32, 32, ColliderType::Overlap), _SScene, false) };

	auto arrowDown{ new Actor(MArrow.name, App::CreateSprite(MArrow.down, 1, 1, MArrow.frame, MArrow.scale), Vector2D(MIDDLE_WIDTH, HALL_WALL - 32), new Collision(32, 32, ColliderType::Overlap))};

	TriggerScene* loungeTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, 0.8), Vector2D(HALL_WALL + TRIGGER_OFFSET, MIDDLE_HEIGHT), Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS - 32, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _WScene, false) };

	auto arrowLeft{ new Actor(MArrow.name, App::CreateSprite(MArrow.left, 1, 1, MArrow.frame, MArrow.scale), Vector2D(HALL_WALL - 32, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap)) };

	TriggerScene* libraryTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, 0.8), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT),Vector2D(LIBRARY_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS, MIDDLE_HEIGHT),  new Collision(32, 32, ColliderType::Overlap), _EScene, false) };

	auto arrowRight{ new Actor(MArrow.name, App::CreateSprite(MArrow.right, 1, 1, MArrow.frame, MArrow.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL + 32, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap)) };

	TriggerScene* roomTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MTriggerScene.model, 2, 1, MTriggerScene.frame, MTriggerScene.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL), Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS + 16), new Collision(32, 32, ColliderType::Overlap, Vector2D(0, -24)), _NScene, false) };

	auto arrowUp{ new Actor(MArrow.name, App::CreateSprite(MArrow.up, 1, 1, MArrow.frame, MArrow.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL + 64), new Collision(32, 32, ColliderType::Overlap)) };

	roomTrigger->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_DOOR, 1 / 15.f, { 0, 1 });

	doors.emplace_back(entranceTrigger);
	doors.emplace_back(loungeTrigger);
	doors.emplace_back(libraryTrigger);
	doors.emplace_back(roomTrigger);

	/*PROPS*/

	auto carpet{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(64, 64, ColliderType::Overlap)) };

	std::vector<Vector2D> v{ Vector2D(MIDDLE_WIDTH + 2, MIDDLE_HEIGHT + 70), Vector2D(450, MIDDLE_HEIGHT + 40), Vector2D(576, MIDDLE_HEIGHT + 40), Vector2D(462, MIDDLE_HEIGHT - 28), Vector2D(564, MIDDLE_HEIGHT - 28) };
	for (int i = 0; i < v.size(); ++i)
	{
		_candles.emplace_back(new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), v[i], new Collision(10, 10)));
		_candles[i]->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
		_candles[i]->_SInteract = SFX.item_pick;
		_candlePuzzle->GetCandles().emplace_back(_candles[i]);
	}

	ObjectController* objectC{ new ObjectController(false) };

	// Characters

	auto pentagramme{ new Actor(MPentagramme.name, App::CreateSprite(MPentagramme.model, 4, 4, 0, 3), Vector2D(MIDDLE_WIDTH + 4, MIDDLE_HEIGHT + 32), new Collision(48, 32, ColliderType::Overlap)) };
	pentagramme->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);

	auto pillar{ new Character(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), Vector2D(MIDDLE_WIDTH - 48, APP_VIRTUAL_HEIGHT - HALL_WALL - 16), new Collision(32, 16), 0, 4, objectC) };
	pillar->SetDirection(Direction::DOWN);

	auto pillar2{ new Character(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), Vector2D(MIDDLE_WIDTH + 48, APP_VIRTUAL_HEIGHT - HALL_WALL - 16), new Collision(32, 16), 0, 6, objectC) };
	pillar2->SetDirection(Direction::DOWN);

	auto picture{ new Character(MPicture.name, App::CreateSprite(MPicture.model, 1, 1, MPicture.frame, MPicture.scale), Vector2D(MIDDLE_WIDTH - 130, APP_VIRTUAL_HEIGHT - HALL_WALL + TRIGGER_OFFSET), new Collision(32, 32), 0, 8, objectC) };
	auto picture2{ new Character(MPicture.name, App::CreateSprite(MPicture.model2, 1, 1, MPicture.frame, MPicture.scale), Vector2D(MIDDLE_WIDTH + 96, APP_VIRTUAL_HEIGHT - HALL_WALL + TRIGGER_OFFSET), new Collision(32, 32), 0, 7, objectC) };

	auto table{ new Character(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), Vector2D(HALL_WALL + 64, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET), new Collision(32, 32), 0, 4, objectC) };
	table->SetDirection(Direction::DOWN);

	auto commode{ new Character(MCommode.name, App::CreateSprite(MCommode.model, 1, 1, MCommode.frame, MCommode.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 96, APP_VIRTUAL_HEIGHT - HALL_WALL - 8), new Collision(16, 32), 0, 5, objectC) };
	commode->SetDirection(Direction::DOWN);

	auto commode3{ new Character(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 16, HALL_WALL + 64), new Collision(64, 32), 0, 4, objectC) };
	commode3->SetDirection(Direction::LEFT);

	auto commode4{ new Character(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 16, APP_VIRTUAL_HEIGHT - HALL_WALL - 64), new Collision(64, 32), 0, 6, objectC) };
	commode4->SetDirection(Direction::LEFT);

	auto commode5{ new Character(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), Vector2D(HALL_WALL + 16, HALL_WALL + 64), new Collision(64, 32), 0, 3, objectC) };
	commode5->SetDirection(Direction::RIGHT);

	auto commode6{ new Character(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), Vector2D(HALL_WALL + 16, APP_VIRTUAL_HEIGHT - HALL_WALL - 64), new Collision(64, 32), 0, 4, objectC) };
	commode6->SetDirection(Direction::RIGHT);

	auto candle{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 144, APP_VIRTUAL_HEIGHT - HALL_WALL - 16), new Collision(30, 10)) }; candle->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true); candle->GetSprite()->SetAnimation(CSimpleSprite::ANIM_CANDLE);
	auto candle2{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 120, APP_VIRTUAL_HEIGHT - HALL_WALL - 16), new Collision(30, 10)) }; candle2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true); candle2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_CANDLE);

	auto candle4{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 96, APP_VIRTUAL_HEIGHT - HALL_WALL - 16), new Collision(30, 10)) }; candle4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true); candle4->GetSprite()->SetAnimation(CSimpleSprite::ANIM_CANDLE);

	auto skull{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(HALL_WALL + 80, HALL_WALL + 128), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull2{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 50, HALL_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull4{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(MIDDLE_WIDTH + 120, MIDDLE_HEIGHT + 100), new Collision(32, 32, ColliderType::Overlap)) };

	auto web{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(HALL_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 80), new Collision(32, 32, ColliderType::Overlap)) };
	auto web2{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web3{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(HALL_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 144), new Collision(32, 32, ColliderType::Overlap)) };
	auto web4{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 176), new Collision(32, 32, ColliderType::Overlap)) };
	auto web5{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(HALL_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 208), new Collision(32, 32, ColliderType::Overlap)) };
	auto web6{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 240), new Collision(32, 32, ColliderType::Overlap)) };
	auto web7{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(HALL_WALL + 16, ENTRANCE_WALL + 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web8{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - 16, ENTRANCE_WALL + 48), new Collision(32, 32, ColliderType::Overlap)) };

	auto blood{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH - 150, MIDDLE_HEIGHT + 64), new Collision(32, 32, ColliderType::Overlap)) };
	auto blood2{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH + 150, MIDDLE_HEIGHT - 90), new Collision(32, 32, ColliderType::Overlap)) };

	/*NPC*/
	auto jones{ new NPC("\"Bright\" Jones", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT + 20), new Collision(32, 32)) };
	jones->dialogues.insert(std::make_pair(0, DJones.h1));
	jones->SetCurrentDialogue(0);

	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, MCharlotte.frame, MCharlotte.scale), Vector2D(MIDDLE_WIDTH - 64, MIDDLE_HEIGHT - 96), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.h1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.h2));
	charlotte->SetCurrentDialogue(0);


	/*Start Puzzle*/
	_candlePuzzle->StartPuzzle();
	_candlePuzzle->onSolved += [this, pentagramme]() {	pentagramme->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME); };

	Trigger* trigger{ new Trigger(MTriggerScene.name, App::CreateSprite(), Vector2D(MIDDLE_WIDTH, HALL_WALL + 32), new Collision(32, APP_VIRTUAL_WIDTH - HALL_WALL * 2, ColliderType::Overlap)) };

	//Close the Entrance door 
	trigger->onTriggered += [this, entranceTrigger]() 
	{
		entranceTrigger->OnDeactivation(); 
		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
		if (!stateDialogue)
			return;

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_locked);
		StateController::SetState(State::DIALOGUE);
	};

	Trigger* trigger2{ new Trigger(MTriggerScene.name, App::CreateSprite(), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS), new Collision(32, APP_VIRTUAL_WIDTH - HALL_WALL * 2, ColliderType::Overlap), false) };
	trigger2->SetTag("Close Room");
	
	trigger2->onTriggered += [this, roomTrigger]()
	{
		roomTrigger->OnDeactivation();
		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
		if (!stateDialogue)
			return;

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_locked);
		StateController::SetState(State::DIALOGUE);

		roomTrigger->GetSprite()->SetFrame(0);
	};

	Trigger* trigger3{ new Trigger(MTriggerScene.name, App::CreateSprite(), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT + 20), new Collision(32, APP_VIRTUAL_WIDTH - HALL_WALL * 2, ColliderType::Overlap), false) };
	trigger3->SetTag("Open Library");

	trigger3->onTriggered += [this, libraryTrigger]()
	{
		libraryTrigger->OnActivation();
		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
		if (!stateDialogue)
			return;

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_unlocked);
		StateController::SetState(State::DIALOGUE);
	};

}

void Hall::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Hall::Render()
{
	Scene::Render();
}

void Hall::Exit()
{
}

bool Hall::IsRoomCleared()
{
	if (!_candlePuzzle)
		return false;
	 
	if (!_candlePuzzle->IsCleared())
		return false;

	else if (_candlePuzzle->GetStatus() == Status::CLEARED)
		return true;

	else if (_candlePuzzle->GetStatus() == Status::PENDING)
	{
		auto it{ std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "\"Bright\" Jones"; }) };
		if (it != _actors.end())
		{
			CSimpleSound::GetInstance().PlaySoundW((*it)->_SInteract, 0);
			RemoveActor(*it);
		}

		auto npc{ std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == MCharlotte.name; }) };
		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}
	}

	if (_candlePuzzle->_page->isItemized() && _candlePuzzle->GetStatus() == Status::PENDING)
	{
		_candlePuzzle->onSolved();
		_candlePuzzle->SetStatus(Status::CLEARED);

		// Looking for the doors to open
		for (auto& door : doors)
		{
			if (door->_scene == _NScene)
			{
				auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };

				if (!stateDialogue)
					return true;

				stateDialogue->_currentDialogue.emplace_back(MMessage.door_unlocked);
				StateController::SetState(State::DIALOGUE);

				door->GetSprite()->SetAnimation(CSimpleSprite::ANIM_DOOR);
				CSimpleSound::GetInstance().PlaySoundW(SFX.door_open, 0);

				door->SetActivation(true);
				break;
			}
		}
		return true;
	}
	return false;
}