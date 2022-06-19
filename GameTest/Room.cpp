#include "../stdafx.h"
#include "Room.h"

Room::Room(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Room::Room(int ID) : Scene(ID)
{
}

Room::~Room()
{
}

bool Room::Init()
{
	if (initialized)
		return true;

	std::random_device myRandomDevice;
	/*Background First*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - ROOM_WALL_OFFSET * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - ROOM_WALL_OFFSET * 2) / 32; i++)
		{
			unsigned seed = myRandomDevice();
			std::default_random_engine myRandomEngine(seed);

			/*if (myRandomEngine() % 12 != 1)*/
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(ROOM_WALL_OFFSET + 16 + i * 32, ROOM_WALL_OFFSET + 16 + j * 32), new Collision(32, 32, Collision::ColliderType::Overlap));
			/*else
				new Actor(MBackground.name, App::CreateSprite(MBackground.model2, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(128 + 16 + i * 32, 128 + 16 + j * 32), new Collision(32, 32, Collision::ColliderType::Overlap));*/
		}
	}

	_mirrorPuzzle = new MirrorPuzzle(MirrorPuzzle::Status::PENDING);

	Mirror* mirror{ new Mirror(MMirror.name, App::CreateSprite(MMirror.model, 6, 1, MMirror.frame, MMirror.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL_OFFSET - 32), new Collision(32, 32)) };
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_BROKEN, 1.0f / 10.0f, { 0,1,2,3,4,5 });
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_REPAIRED, 1.0f / 10.0f, { 5,4,3,2,1,0 });
	mirror->SetMobility(Mobility::MOVABLE);

	_mirrorPuzzle->_mirror = mirror;

	// Triggers
	TriggerScene* hallTrigger = new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, ROOM_WALL_OFFSET + TRIGGER_OFFSET), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - ROOM_WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET), new Collision(32, 32, Collision::ColliderType::Overlap), _SScene);

	TriggerDialogue* dialogueTrigger{ new TriggerDialogue(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, ROOM_WALL_OFFSET + TRIGGER_OFFSET + 92), new Collision(32, APP_VIRTUAL_WIDTH - ROOM_WALL_OFFSET * 2, Collision::ColliderType::Overlap), StateMain::_player->dialogues[0]) };

	TriggerAnimation* m{ new TriggerAnimation(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale),  new Vector2D(MIDDLE_WIDTH, ROOM_WALL_OFFSET + TRIGGER_OFFSET + 92), new Collision(32, APP_VIRTUAL_WIDTH - ROOM_WALL_OFFSET * 2, Collision::ColliderType::Overlap), true) };
	m->_targetAnim = CSimpleSprite::ANIM_MIRROR_BROKEN;
	m->_targetSprite = mirror->GetSprite();
	m->_SInteract = SFX.mirror_repaired;
	m->_onPlayingAnim += [this]() {this->OnMirrorShattered(); };

	/*MirrorShard* shard2{ new MirrorShard(MMirrorShard.name + "2", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150,350), new Collision(32, 32)) };

	MirrorShard* shard3{ new MirrorShard(MMirrorShard.name + "3", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150,400), new Collision(32, 32)) };

	MirrorShard* shard4{ new MirrorShard(MMirrorShard.name + "4", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150, 450), new Collision(32, 32)) };*/

	ObjectController* objectC{ new ObjectController() };
	Character* character{ new Character(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), new Vector2D(350,250), new Collision(32, 32), 0, 4, objectC) };
	character->SetMobility(Mobility::MOVABLE);

	/*PROPS*/

	auto bed{ new Actor(MBed.name, App::CreateSprite(MBed.model, 1, 1, MBed.frame, MBed.scale), new Vector2D(ROOM_WALL_OFFSET + 32, APP_VIRTUAL_HEIGHT - ROOM_WALL_OFFSET - 64), new Collision(48, 32)) };

	/*Start Puzzle*/
	_mirrorPuzzle->StartPuzzle();

	initialized = !initialized;

	return true;
}

void Room::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Room::Render()
{
	Scene::Render();
}

bool Room::IsRoomCleared()
{
	if (!_mirrorPuzzle)
		return false;

	if (!_mirrorPuzzle->IsCleared())
		return false;

	else if (_mirrorPuzzle->_status == Puzzle::Status::CLEARED)
		return true;

	else if (_mirrorPuzzle->_status == Puzzle::Status::PENDING)
	{
		std::string description = "No";

		auto page{ new Page(MPage.name + " 2" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(512, 394), new Collision(16, 16), 0, description) };
		
		/*auto it = std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Ms. Smith"; });
		if (it != _actors.end())
		{
			RemoveActor(*it);
		}

		auto npc = std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == "Charlotte"; });
		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}*/
		_mirrorPuzzle->_status = Puzzle::Status::CLEARED;

		return true;
	}
}

void Room::OnMirrorShattered()
{
	MirrorShard* shard1{ new MirrorShard(MMirrorShard.name + "1", App::CreateSprite(MPage.model , 1, 1), new Vector2D(MIDDLE_WIDTH + 128, APP_VIRTUAL_HEIGHT - ROOM_WALL_OFFSET - 150), new Collision(32, 32)) };
	_SScene->GetActors().emplace_back((new MirrorShard(MMirrorShard.name + "2", App::CreateSprite(MPage.model, 1, 1), new Vector2D(MIDDLE_WIDTH + 150, APP_VIRTUAL_HEIGHT - HALL_WALL_OFFSET - 180), new Collision(32, 32))));
}
