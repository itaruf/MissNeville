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

void Hall::Init()
{
	// Init only once
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);
	StateMain::_player->SetPosition(300, 250);

	/*Background First*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - HALL_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - HALL_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(HALL_WALL + 16 + i * 32, HALL_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(HALL_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - HALL_WALL * 2, 2)) };
	wallLeft->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - HALL_WALL * 2, 2)) };
	wallRight->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, HALL_WALL), new Collision(2, APP_VIRTUAL_WIDTH - HALL_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL), new Collision(2, APP_VIRTUAL_WIDTH - HALL_WALL * 2)) };
	wallTop->SetTag("wall");

	/*Initiating Puzzles*/
	/*_candlePuzzle = new CandlePuzzle(Status::PENDING);*/

	/*Triggers*/

	TriggerScene* entranceTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, HALL_WALL + TRIGGER_OFFSET), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS - 16), new Collision(32, 32, ColliderType::Overlap), _SScene, false) };

	TriggerScene* loungeTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(HALL_WALL + TRIGGER_OFFSET, MIDDLE_HEIGHT), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS - 32, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _WScene, true) };

	TriggerScene* libraryTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(LIBRARY_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS, MIDDLE_HEIGHT),  new Collision(32, 32, ColliderType::Overlap), _EScene, false) };

	TriggerScene* roomTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MTriggerScene.model, 2, 1, MTriggerScene.frame, MTriggerScene.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL), new Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS), new Collision(32, 32, ColliderType::Overlap, new Vector2D(0, -24)), _NScene, false) };
	roomTrigger->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_DOOR, 1 / 15.f, { 0, 1 });
	roomTrigger->_SInteract = SFX.door_open;

	doors.emplace_back(entranceTrigger);
	doors.emplace_back(loungeTrigger);
	doors.emplace_back(libraryTrigger);
	doors.emplace_back(roomTrigger);

	/*PROPS*/

	auto carpet{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale), new Vector2D(512, 384), new Collision(64, 64, ColliderType::Overlap)) };

	std::vector<Vector2D*> v{ new Vector2D(514,466), new Vector2D(446,432), new Vector2D(580,432), new Vector2D(460,356), new Vector2D(564,356) };
	for (int i = 0; i < v.size(); ++i)
	{
		_candles.emplace_back(new Candle(MCandle.name, App::CreateSprite(MCandle.model, 1, 2, MCandle.frame, MCandle.scale), v[i], new Collision(10, 10)));
		_candles[i]->_SInteract = SFX.item_pick;
		_candlePuzzle->GetCandles().emplace_back(_candles[i]);
	}

	auto pentagramme{ new Actor(MPentagramme.name, App::CreateSprite(MPentagramme.model, 4, 4, 0, 3), new Vector2D(516, 418), new Collision(48, 32, ColliderType::Overlap)) };

	auto pillar{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), new Vector2D(MIDDLE_WIDTH - 70, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET), new Collision(32, 16)) };
	auto pillar2{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), new Vector2D(MIDDLE_WIDTH + 70, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET), new Collision(32, 16)) };

	auto railing{ new Actor(MRailing.name, App::CreateSprite(MRailing.model, 1, 1, MRailing.frame, MRailing.scale), new Vector2D(MIDDLE_WIDTH - 40, APP_VIRTUAL_HEIGHT - HALL_WALL), new Collision(32, 16)) };
	auto railing2{ new Actor(MRailing.name, App::CreateSprite(MRailing.model, 1, 1, MRailing.frame, MRailing.scale), new Vector2D(MIDDLE_WIDTH + 40, APP_VIRTUAL_HEIGHT - HALL_WALL), new Collision(32, 16)) };

	auto picture{ new Actor(MPicture.name, App::CreateSprite(MPicture.model, 1, 1, MPicture.frame, MPicture.scale), new Vector2D(MIDDLE_WIDTH - 150, APP_VIRTUAL_HEIGHT - HALL_WALL + TRIGGER_OFFSET), new Collision(32, 32)) };
	auto picture2{ new Actor(MPicture.name, App::CreateSprite(MPicture.model2, 1, 1, MPicture.frame, MPicture.scale), new Vector2D(MIDDLE_WIDTH + 150, APP_VIRTUAL_HEIGHT - HALL_WALL + TRIGGER_OFFSET), new Collision(32, 32)) };

	auto table{ new Actor(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), new Vector2D(HALL_WALL + 64, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET), new Collision(32, 32)) };

	auto commode{ new Actor(MCommode.name, App::CreateSprite(MCommode.model, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(HALL_WALL + 128, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET), new Collision(16, 32)) };

	/*NPC*/
	auto jones{ new NPC("\"Bright\" Jones", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), new Vector2D(512, 394), new Collision(32, 32)) };
	jones->dialogues.insert(std::make_pair(0, DJones.h1));
	jones->SetCurrentDialogue(0);

	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, MCharlotte.frame, MCharlotte.scale), new Vector2D(300, 300), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.h1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.h2));
	charlotte->SetCurrentDialogue(0);

	ObjectController* objectC{ new ObjectController() };

	/*Start Puzzle*/
	_candlePuzzle->StartPuzzle();

	Trigger* trigger{ new Trigger(MTriggerScene.name, App::CreateSprite(), new Vector2D(MIDDLE_WIDTH, HALL_WALL + 32), new Collision(32, APP_VIRTUAL_WIDTH - HALL_WALL * 2, ColliderType::Overlap)) };

	//Close the Entrance door 
	trigger->_onTriggered += [this, entranceTrigger]() 
	{
		entranceTrigger->OnDeactivation(); 
		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
		if (!stateDialogue)
			return;

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_locked);
		StateMain::SetState(State::DIALOGUE);
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

	else if (_candlePuzzle->_status == Status::CLEARED)
		return true;

	else if (_candlePuzzle->_status == Status::PENDING)
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

	if (_candlePuzzle->_page->itemized && _candlePuzzle->_status == Status::PENDING)
	{
		_candlePuzzle->_status = Status::CLEARED;

		// Looking for the doors to open
		for (auto& door : doors)
		{
			if (door->_scene == _NScene)
			{
				auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

				if (!stateDialogue)
					return true;

				stateDialogue->_currentDialogue.emplace_back(MMessage.door_unlocked);
				StateMain::SetState(State::DIALOGUE);

				door->GetSprite()->SetAnimation(CSimpleSprite::ANIM_DOOR);
				CSimpleSound::GetInstance().PlaySoundW(SFX.door_open, 0);

				door->_activated = true;
				break;
			}
		}
		return true;
	}
	return false;
}


