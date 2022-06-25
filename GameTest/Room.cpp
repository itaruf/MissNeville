#include "../stdafx.h"
#include "Room.h"

Room::Room(int ID) : Scene(ID)
{
}

Room::Room(int ID, MirrorPuzzle* mirrorPuzzle) : Scene(ID), _mirrorPuzzle(mirrorPuzzle)
{
}

Room::~Room()
{
}

void Room::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);

	/*Background First*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - ROOM_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - ROOM_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(ROOM_WALL + 16 + i * 32, ROOM_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(ROOM_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + ROOM_WALL, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, ROOM_WALL), new Collision(2, MIDDLE_WIDTH + ROOM_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL), new Collision(2, MIDDLE_WIDTH + ROOM_WALL * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + ROOM_WALL, 2)) };
	wallRight->SetTag("wall");

	/*PROPS*/

	auto bed{ new Actor(MBed.name, App::CreateSprite(MBed.model, 1, 1, MBed.frame, MBed.scale), new Vector2D(ROOM_WALL + 32, APP_VIRTUAL_HEIGHT - ROOM_WALL - 32), new Collision(48, 32)) };

	auto table{ new Actor(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), new Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 32), new Collision(32, 32)) };

	auto commode{ new Actor(MCommode.name, App::CreateSprite(MCommode.model, 1, 1, MCommode.frame, MCommode.scale),  new Vector2D(APP_VIRTUAL_WIDTH - ROOM_WALL - 64, APP_VIRTUAL_HEIGHT - ROOM_WALL), new Collision(16, 32)) };
	auto commode2{ new Actor(MCommode.name, App::CreateSprite(MCommode.model3, 1, 1, MCommode.frame, MCommode.scale2),  new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL - 16), new Collision(16, 32)) };

	auto shelf{ new Actor(MCommode.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame,  MShelf.scale),  new Vector2D(MIDDLE_WIDTH + 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 8), new Collision(16, 32)) };
	auto shelf2{ new Actor(MCommode.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame,  MShelf.scale),  new Vector2D(shelf->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - ROOM_WALL - 8), new Collision(16, 32)) };

	/*Instantiating puzzle*/
	/*_mirrorPuzzle = new MirrorPuzzle(Status::PENDING);*/

	Mirror* mirror{ new Mirror(MMirror.name, App::CreateSprite(MMirror.model, 6, 1, MMirror.frame, MMirror.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL + 20), new Collision(96, 32)) };
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_BROKEN, 1.0f / 10.0f, { 0,1,2,3,4,5 });
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_REPAIRED, 1.0f / 10.0f, { 5,4,3,2,1,0 });
	mirror->SetMobility(Mobility::MOVABLE);

	_mirrorPuzzle->_mirror = mirror;

	/*Open the library door*/
	auto it = std::find_if(StateMain::_rooms[1]->GetActors().begin(), StateMain::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateMain::_rooms[1]->_EScene; });

	if (it != StateMain::_rooms[1]->GetActors().end())
		mirror->_onInteract += [this, it]() {dynamic_cast<TriggerScene*>(*it)->OnActivation(); };


	// Triggers
	TriggerScene* hallTrigger = new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - HALL_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS), new Collision(32, 32, ColliderType::Overlap), _SScene);

	TriggerDialogue* dialogueTrigger{ new TriggerDialogue(MTriggerScene.name, App::CreateSprite("", 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET + 80), new Collision(16, APP_VIRTUAL_WIDTH - ROOM_WALL * 2, ColliderType::Overlap), StateMain::_player->dialogues[0]) };

	TriggerAnimation* mirrorAnimTrigger{ new TriggerAnimation(MTriggerScene.name, App::CreateSprite("", 1, 1, MIcon.frame, MIcon.scale),  new Vector2D(MIDDLE_WIDTH, ROOM_WALL + TRIGGER_OFFSET + 80), new Collision(16, APP_VIRTUAL_WIDTH - ROOM_WALL * 2, ColliderType::Overlap), true)};
	mirrorAnimTrigger->_targetAnim = CSimpleSprite::ANIM_MIRROR_BROKEN;
	mirrorAnimTrigger->_targetSprite = mirror->GetSprite();
	mirrorAnimTrigger->_SInteract = SFX.mirror_repaired;
	mirrorAnimTrigger->_onPlayingAnim += [this]() {this->OnMirrorShattered(); };

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

	else if (_mirrorPuzzle->_status == Status::CLEARED)
		return true;

	else if (_mirrorPuzzle->_status == Status::PENDING)
	{
		auto page{ new Page(MPage.name + " 4" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(512, 394), new Collision(16, 16), 0, DPage.p4) };
		
		// Open the Entrance door once the page is collected
		auto it = std::find_if(StateMain::_rooms[1]->GetActors().begin(), StateMain::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateMain::_rooms[1]->_SScene; });

		if (it != StateMain::_rooms[1]->GetActors().end())
		{
			page->_onCollected += [this, it]() {dynamic_cast<TriggerScene*>(*it)->OnActivation(); };
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

		_mirrorPuzzle->_status = Status::CLEARED;
		_mirrorPuzzle->_onSolved();

		return true;
	}
}

void Room::OnMirrorShattered()
{
	MirrorShard* shard1{ new MirrorShard(MMirrorShard.name + "1", App::CreateSprite(MPage.model , 1, 1), new Vector2D(MIDDLE_WIDTH + 128, APP_VIRTUAL_HEIGHT - ROOM_WALL - 150), new Collision(32, 32)) };

	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, MCharlotte.frame, MCharlotte.scale), new Vector2D(MIDDLE_WIDTH + 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 64), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.r1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.r2));
	charlotte->SetCurrentDialogue(0);

	auto maggy{ new NPC("Maggy Smith", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), new Vector2D(MIDDLE_WIDTH - 64, APP_VIRTUAL_HEIGHT - ROOM_WALL - 64), new Collision(32, 32))};
	maggy->dialogues.insert(std::make_pair(0, DSmith.r1));
	maggy->SetCurrentDialogue(0);
}
