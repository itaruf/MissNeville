#include "../stdafx.h"
#include "Room.h"

Room::Room(int ID) : Scene(ID)
{
}

Room::Room(int ID, MirrorPuzzle* mirrorPuzzle) : Scene(ID), _mirrorPuzzle(mirrorPuzzle)
{
}

void Room::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateController::_player);

	/*Background First*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - ROOM_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - ROOM_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), Vector2D(ROOM_WALL + 16 + i * 32, ROOM_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(ROOM_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + ROOM_WALL, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, ROOM_WALL), new Collision(2, MIDDLE_WIDTH + ROOM_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL), new Collision(2, MIDDLE_WIDTH + ROOM_WALL * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + ROOM_WALL, 2)) };
	wallRight->SetTag("wall");

	/*PROPS*/

	auto bed{ new Actor(MBed.name, App::CreateSprite(MBed.model, 1, 1, MBed.frame, MBed.scale), Vector2D(ROOM_WALL + 32, APP_VIRTUAL_HEIGHT - ROOM_WALL - 32), new Collision(48, 32)) };

	auto table{ new Actor(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 64, ROOM_WALL + 16), new Collision(32, 32)) };
	auto candle{ new Candle(MCandle.name, App::CreateSprite(MCandle.model, 7, 2, MCandle.frame, MCandle.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 64, ROOM_WALL + 32), new Collision(30, 10)) }; candle->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_CANDLE, 1 / 15.f, { 7, 8, 9, 10, 11, 12, 13 }, true); candle->GetSprite()->SetAnimation(CSimpleSprite::ANIM_CANDLE);

	auto commode{ new Actor(MCommode.name, App::CreateSprite(MCommode.model, 1, 1, MCommode.frame, MCommode.scale),  Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 64, APP_VIRTUAL_HEIGHT - ROOM_WALL), new Collision(16, 32)) };
	auto commode2{ new Actor(MCommode.name, App::CreateSprite(MCommode.model3, 1, 1, MCommode.frame, MCommode.scale2),  Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL - 16), new Collision(16, 32)) };

	auto shelf{ new Actor(MCommode.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame,  MShelf.scale),  Vector2D(MIDDLE_WIDTH + 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 8), new Collision(16, 32)) };
	auto shelf2{ new Actor(MCommode.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame,  MShelf.scale),  Vector2D(shelf->GetPosition().x + 32, APP_VIRTUAL_HEIGHT - ROOM_WALL - 8), new Collision(16, 32)) };

	auto skull{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(ROOM_WALL + 80, ROOM_WALL + 80), new Collision(32, 32, ColliderType::Overlap)) };
	//auto skull2{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 50, ROOM_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull3{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(MIDDLE_WIDTH - 44, MIDDLE_HEIGHT + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull4{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(MIDDLE_WIDTH + 96, MIDDLE_HEIGHT + 100), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull5{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), Vector2D(MIDDLE_WIDTH + 70, MIDDLE_HEIGHT - 80), new Collision(32, 32, ColliderType::Overlap)) };

	auto web2{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web3{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(ROOM_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 144), new Collision(32, 32, ColliderType::Overlap)) };
	auto web4{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 176), new Collision(32, 32, ColliderType::Overlap)) };
	auto web5{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), Vector2D(ROOM_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 208), new Collision(32, 32, ColliderType::Overlap)) };
	auto web6{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 240), new Collision(32, 32, ColliderType::Overlap)) };

	auto blood{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH - 150, MIDDLE_HEIGHT + 64), new Collision(32, 32, ColliderType::Overlap)) };
	auto blood2{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), Vector2D(MIDDLE_WIDTH + 90, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap)) };

	auto picture{ new Actor(MPicture.name, App::CreateSprite(MPicture.model, 1, 1, MPicture.frame, MPicture.scale), Vector2D(MIDDLE_WIDTH - 96, APP_VIRTUAL_HEIGHT - ROOM_WALL + TRIGGER_OFFSET), new Collision(32, 32)) };

	Mirror* mirror{ new Mirror(MMirror.name, App::CreateSprite(MMirror.model, 6, 1, MMirror.frame, MMirror.scale), Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL + 20), new Collision(96, 32)) };
	mirror->SetTag("Mirror");
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_BROKEN, 1.0f / 10.0f, { 0,1,2,3,4,5 });
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_REPAIRED, 1.0f / 10.0f, { 5,4,3,2,1,0 });
	mirror->SetMobility(Mobility::MOVABLE);

	_mirrorPuzzle->SetMirror(mirror);
	_mirrorPuzzle->onSolved += [this]()
	{
		auto it = std::find_if(StateController::_rooms[1]->GetActors().begin(), StateController::_rooms[1]->GetActors().end(), [](Actor* actor) { return actor->GetName() == MCharlotte.name; });
		if (it != StateController::_rooms[1]->GetActors().end())
		{
			StateController::_rooms[1]->RemoveActor(*it);
		}

		// Close the library
		auto it2 = std::find_if(StateController::_rooms[1]->GetActors().begin(), StateController::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateController::_rooms[1]->_EScene; });

		if (it2 != StateController::_rooms[1]->GetActors().end())
			dynamic_cast<TriggerScene*>(*it2)->SetActivation(false);

		// Close the kitchen
		auto it3 = std::find_if(StateController::_rooms[1]->GetActors().begin(), StateController::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateController::_rooms[1]->_WScene; });

		if (it3 != StateController::_rooms[1]->GetActors().end())
			dynamic_cast<TriggerScene*>(*it3)->SetActivation(false);

		// Open the entrance
		auto it5 = std::find_if(StateController::_rooms[5]->GetActors().begin(), StateController::_rooms[5]->GetActors().end(), [](Actor* actor) { return actor->GetTag() == "Close Entrance"; });

		if (it5 != StateController::_rooms[5]->GetActors().end())
			dynamic_cast<Trigger*>(*it5)->SetActivation(true);

		// Activate the trigger which will close the room behind the player
		auto it4 = std::find_if(StateController::_rooms[1]->GetActors().begin(), StateController::_rooms[1]->GetActors().end(), [](Actor* actor) { return actor->GetTag() == "Close Room"; });

		if (it4 != StateController::_rooms[1]->GetActors().end())
			dynamic_cast<Trigger*>(*it4)->SetActivation(true);
	};

	// Triggers
	TriggerScene* hallTrigger = new TriggerScene(MTriggerScene.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, 0.8), Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET), Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT + 20), new Collision(32, 32, ColliderType::Overlap), _SScene);

	auto arrowDown{ new Actor(MArrow.name, App::CreateSprite(MArrow.down, 1, 1, MArrow.frame, MArrow.scale), Vector2D(MIDDLE_WIDTH, ROOM_WALL - 32), new Collision(32, 32, ColliderType::Overlap)) };

	TriggerDialogue* dialogueTrigger{ new TriggerDialogue(MTriggerScene.name, App::CreateSprite("", 1, 1, MIcon.frame, MIcon.scale), Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET + 96), new Collision(16, APP_VIRTUAL_WIDTH - ROOM_WALL * 2, ColliderType::Overlap), DDetective.r1) };

	TriggerAnimation* mirrorAnimTrigger{ new TriggerAnimation(MTriggerScene.name, App::CreateSprite("", 1, 1, MIcon.frame, MIcon.scale),  Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET + 96), new Collision(16, APP_VIRTUAL_WIDTH - ROOM_WALL * 2, ColliderType::Overlap), true)};
	mirrorAnimTrigger->targetAnim = CSimpleSprite::ANIM_MIRROR_BROKEN;
	mirrorAnimTrigger->targetSprite = mirror->GetSprite();
	mirrorAnimTrigger->_SInteract = SFX.mirror_repaired;
	mirrorAnimTrigger->onPlayingAnim += [this]() 
	{this->OnMirrorShattered(); };
	mirrorAnimTrigger->onTriggered += [this]()
	{
		auto it = std::find_if(StateController::_rooms[1]->GetActors().begin(), StateController::_rooms[1]->GetActors().end(), [](Actor* actor) { return actor->GetTag() == "Open Library"; });

		if (it != StateController::_rooms[1]->GetActors().end())
			dynamic_cast<Trigger*>(*it)->SetActivation(true);
	};

	/*Start Puzzle*/
	_mirrorPuzzle->StartPuzzle();
}

void Room::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Room::Render()
{
	Scene::Render();
}

void Room::Exit()
{
}

bool Room::IsRoomCleared()
{
	if (!_mirrorPuzzle)
		return false;

	if (!_mirrorPuzzle->IsCleared())
		return false;

	else if (_mirrorPuzzle->GetStatus() == Status::CLEARED)
		return true;

	else if (_mirrorPuzzle->GetStatus() == Status::PENDING)
	{
		auto page{ new Page(MPage.name + " 4" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), Vector2D(512, 394), new Collision(16, 16), 0, DProps.p4) };
		
		// Open the Entrance door once the page is collected
		auto it = std::find_if(StateController::_rooms[1]->GetActors().begin(), StateController::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateController::_rooms[1]->_SScene; });

		if (it != StateController::_rooms[1]->GetActors().end())
		{
			page->onCollected += [this, it]() 
			{
				dynamic_cast<TriggerScene*>(*it)->OnActivation();
				auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };

				if (!stateDialogue)
					return true;

				stateDialogue->_currentDialogue.emplace_back(MMessage.door_unlocked);
				stateDialogue->_currentDialogue.emplace_back(DDetective.r3);

				StateController::SetState(State::DIALOGUE);
			};
		}
		
		auto it2 = std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Maggy Smith"; });
		if (it2 != _actors.end())
		{
			RemoveActor(*it2);
		}

		auto npc = std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == MCharlotte.name; });

		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}
		_mirrorPuzzle->SetStatus(Status::CLEARED);
		_mirrorPuzzle->onSolved();

		return true;
	}
}

void Room::OnMirrorShattered()
{
	MirrorShard* shard1{ new MirrorShard(MMirrorShard.name + "1", App::CreateSprite(MPage.model , 1, 1, 1, 2), Vector2D(MIDDLE_WIDTH + 128, APP_VIRTUAL_HEIGHT - ROOM_WALL - 150), new Collision(32, 32)) };

	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, MCharlotte.frame, MCharlotte.scale), Vector2D(MIDDLE_WIDTH + 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 64), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.r1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.r2));
	charlotte->SetCurrentDialogue(0);

	auto maggy{ new NPC("Maggy Smith", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), Vector2D(MIDDLE_WIDTH - 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 64), new Collision(32, 32))};
	maggy->dialogues.insert(std::make_pair(0, DSmith.r1));
	maggy->SetCurrentDialogue(0);
}