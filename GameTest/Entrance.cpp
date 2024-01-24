#include "../stdafx.h"
#include "Entrance.h"

Entrance::Entrance(int ID) : Scene(ID)
{
}

void Entrance::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateController::_player);
	StateController::_player->GetSprite()->SetPosition(MIDDLE_WIDTH, ENTRANCE_WALL + 64);

	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - ENTRANCE_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), Vector2D(ENTRANCE_WIDTH_WALL + 16 + i * 32, ENTRANCE_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(ENTRANCE_WIDTH_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - ENTRANCE_WALL * 2, 2)) };
	wallLeft->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - ENTRANCE_WALL * 2, 2)) };
	wallRight->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL), new Collision(2, APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL), new Collision(2, APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL * 2)) };
	wallTop->SetTag("wall");

	/*PROPS*/

	auto carpet{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL + 48), new Collision(64, 64, ColliderType::Overlap)) };
	auto carpet2{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), Vector2D(MIDDLE_WIDTH, carpet->GetPosition().y + 92), new Collision(64, 64, ColliderType::Overlap)) };
	auto carpet3{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), Vector2D(MIDDLE_WIDTH, carpet2->GetPosition().y + 92), new Collision(64, 64, ColliderType::Overlap)) };
	auto carpet4{ new Actor(MCarpet.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, MCarpet.scale2), Vector2D(MIDDLE_WIDTH, carpet3->GetPosition().y + 92), new Collision(64, 64, ColliderType::Overlap)) };

	auto pillar{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), Vector2D(MIDDLE_WIDTH - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL), new Collision(32, 16)) };
	auto pillar2{ new Actor(MPillar.name, App::CreateSprite(MPillar.model, 1, 1, MPillar.frame, MPillar.scale), Vector2D(MIDDLE_WIDTH + 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL), new Collision(32, 16)) };

	auto candle{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, ENTRANCE_WALL + 40), new Collision(30, 10)) }; candle->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle2{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, candle->GetPosition().y + 48), new Collision(30, 10)) }; candle2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle3{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, candle2->GetPosition().y + 48), new Collision(30, 10)) }; candle3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle4{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, candle3->GetPosition().y + 48), new Collision(30, 10)) }; candle4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle5{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, candle4->GetPosition().y + 48), new Collision(30, 10)) }; candle5->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle6{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, candle5->GetPosition().y + 48), new Collision(30, 10)) }; candle6->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle7{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH - 48, candle6->GetPosition().y + 48), new Collision(30, 10)) }; candle7->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);

	auto candle8{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, ENTRANCE_WALL + 40), new Collision(30, 10)) }; candle8->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle9{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, candle8->GetPosition().y + 48), new Collision(30, 10)) }; candle9->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle10{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, candle9->GetPosition().y + 48), new Collision(30, 10)) }; candle10->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle11{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, candle10->GetPosition().y + 48), new Collision(30, 10)) }; candle11->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle12{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, candle11->GetPosition().y + 48), new Collision(30, 10)) }; candle12->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle13{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, candle12->GetPosition().y + 48), new Collision(30, 10)) }; candle13->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);
	auto candle14{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(MIDDLE_WIDTH + 48, candle13->GetPosition().y + 48), new Collision(30, 10)) }; candle14->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true);

	auto web{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(ENTRANCE_WIDTH_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 80), new Collision(32, 32, ColliderType::Overlap)) };
	auto web2{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web3{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(ENTRANCE_WIDTH_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 144), new Collision(32, 32, ColliderType::Overlap)) };
	auto web4{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 176), new Collision(32, 32, ColliderType::Overlap)) };
	auto web5{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(ENTRANCE_WIDTH_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 208), new Collision(32, 32, ColliderType::Overlap)) };
	auto web6{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 240), new Collision(32, 32, ColliderType::Overlap)) };
	auto web7{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(ENTRANCE_WIDTH_WALL + 16, ENTRANCE_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto web8{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 16, ENTRANCE_WALL + 48), new Collision(32, 32, ColliderType::Overlap)) };

	auto blood{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH - 64, MIDDLE_HEIGHT - 64), new Collision(32, 32, ColliderType::Overlap)) };
	auto blood2{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH + 80, MIDDLE_HEIGHT + 80), new Collision(32, 32, ColliderType::Overlap)) };
	auto blood3{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH - 100, MIDDLE_HEIGHT + 150), new Collision(32, 32, ColliderType::Overlap)) };

	auto picture{ new Actor(MPicture.name, App::CreateSprite(MPicture.model, 1, 1, MPicture.frame, MPicture.scale), Vector2D(MIDDLE_WIDTH - 112, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 32), new Collision(32, 32, ColliderType::Overlap)) };
	auto picture2{ new Actor(MPicture.name, App::CreateSprite(MPicture.model2, 1, 1, MPicture.frame, MPicture.scale), Vector2D(MIDDLE_WIDTH + 112, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 32), new Collision(32, 32, ColliderType::Overlap)) };

	auto commode{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), Vector2D(ENTRANCE_WIDTH_WALL + 16, MIDDLE_HEIGHT + 64), new Collision(64, 32)) };
	auto commode2{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), Vector2D(APP_VIRTUAL_WIDTH - ENTRANCE_WIDTH_WALL - 16, MIDDLE_HEIGHT), new Collision(64, 32)) };
	auto commode3{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale4), Vector2D(ENTRANCE_WIDTH_WALL + 8, MIDDLE_HEIGHT - 128), new Collision(64, 32)) };

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MTriggerScene.model, 2, 1, MTriggerScene.frame, MTriggerScene.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 16), Vector2D(MIDDLE_WIDTH, HALL_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS), new Collision(32, 32, ColliderType::Overlap, Vector2D(0, -24)), _NScene, false) };
	hallTrigger->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_DOOR, 1 / 15.0f, { 0, 1 });

	auto arrowUp{ new Actor(MArrow.name, App::CreateSprite(MArrow.up, 1, 1, MArrow.frame, MArrow.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL + 64), new Collision(32, 32, ColliderType::Overlap)) };

	// Trigger Intro
	Trigger* trigger{ new Trigger(MTriggerScene.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT - 64), new Collision(32, 32, ColliderType::Overlap)) };
	trigger->onTriggered += [this]() {	Intro(); };

	/*Opening the door when the dialogue ends*/
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->onDialogueEnd += [this, hallTrigger]() 
	{ 
		hallTrigger->OnActivation(); 
		hallTrigger->GetSprite()->SetAnimation(CSimpleSprite::ANIM_DOOR); 
		CSimpleSound::GetInstance().PlaySoundW(SFX.door_open, 0);
	};

	/*Trigger Outro*/
	// Trigger Candles
	Trigger* trigger2{ new Trigger(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, 0, 2), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT - 64), new Collision(32, 32, ColliderType::Overlap, Vector2D(0, -32)), false)};
	trigger2->SetTag("trap");
	trigger2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	trigger2->_SInteract = SFX.candle_enlight;

	trigger2->onTriggered += [this, trigger2]()
	{
		for (auto& actor : GetActors())
		{
			auto candle{ dynamic_cast<Candle*>(actor) };
			if (!candle) 
				continue;
			candle->GetSprite()->SetAnimation(CSimpleSprite::ANIM_CANDLE);

		}

		CSimpleSound::GetInstance().PlaySoundW(SFX.candle_enlight, 0);
		trigger2->SetActivation(false);

		Outro();
	};

	auto room{ dynamic_cast<Room*>(StateController::_rooms[2]) };
	room->_mirrorPuzzle->onSolved += [this, trigger2]() 
	{
		trigger2->SetActivation(true);

		auto npc = std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == MCharlotte.name; });
		if (npc != _actors.end())
		{
			RemoveActor(*npc);
		}
	};

	// Close the door behind the player
	Trigger* trigger3{ new Trigger(MTriggerScene.name, App::CreateSprite(), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS - 32), new Collision(64, ENTRANCE_WIDTH_WALL, ColliderType::Overlap), false)};
	trigger3->SetTag("Close Entrance");
	trigger3->onTriggered += [this, hallTrigger]()
	{
		hallTrigger->OnDeactivation();
		hallTrigger->GetSprite()->SetFrame(0);

		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };

		if (!stateDialogue)
			return true;

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_locked);
		StateController::SetState(State::DIALOGUE);
	};
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
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->onDialogueEnd.funcs.clear();
}

bool Entrance::IsRoomCleared()
{
	return true;
}

void Entrance::Intro()
{
	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, MCharlotte.frame, MCharlotte.scale), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT + 32), new Collision(32, 32)) };

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(DDetective.e1);
	stateDialogue->_currentDialogue.emplace_back(DCharlotte.e1);
	stateDialogue->_currentDialogue.emplace_back(DDetective.e2);
	stateDialogue->_currentDialogue.emplace_back(DCharlotte.e2);
	StateController::SetState(State::DIALOGUE);

	CSimpleSound::GetInstance().PlaySoundW(SFX.ghost_death, 0);

	stateDialogue->onDialogueEnd += [this, charlotte, stateDialogue]()
	{
		stateDialogue->onDialogueEnd.funcs.clear();
		charlotte->dialogues.insert(std::make_pair(0, DCharlotte.e3));
		charlotte->SetCurrentDialogue(0);
	};
}

void Entrance::Outro()
{
	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, 10, MCharlotte.scale), Vector2D(MIDDLE_WIDTH, ENTRANCE_WALL + 64), new Collision(32, 32)) };

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	StateController::_player->GetController()->SetActivation(false);

	stateDialogue->_currentDialogue.emplace_back(DCharlotte.o1);
	stateDialogue->_currentDialogue.emplace_back(DDetective.o1);
	stateDialogue->_currentDialogue.emplace_back(DCharlotte.o2);
	stateDialogue->_currentDialogue.emplace_back(DDetective.o2);

	StateController::SetState(State::DIALOGUE);

	stateDialogue->onDialogueEnd += [this, stateDialogue]()
	{
		auto trap{ std::find_if(_actors.begin(), _actors.end(), [](Actor* trap) { return trap->GetTag() == "trap"; }) };
		if (trap != _actors.end())
		{
			(*trap)->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
		}

		stateDialogue->Clear();
		stateDialogue->onDialogueEnd.funcs.clear();

		stateDialogue->_currentDialogue.emplace_back(DCharlotte.o3);
		stateDialogue->_currentDialogue.emplace_back(DDetective.o3);
		stateDialogue->_currentDialogue.emplace_back(DCharlotte.o4);

		
		StateController::_player->SetSprite(App::CreateSprite(MFamily.model, 3, 4, 1, MFamily.scale));
		StateController::_player->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_TURN, 1 / 10.0f, { 1,4,7,10 }, true);
		StateController::_player->GetSprite()->SetAnimation(CSimpleSprite::ANIM_TURN);
		StateController::SetState(State::DIALOGUE);

		stateDialogue->onDialogueEnd += [this]() { StateController::LoadScene(6); };
	};

	CSimpleSound::GetInstance().PlaySoundW(SFX.ghost_death, 0);
}