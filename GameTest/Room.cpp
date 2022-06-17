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
	if (Scene::Init())
		return true;

	_mirrorPuzzle = new MirrorPuzzle(MirrorPuzzle::Status::PENDING);

	// Triggers
	TriggerScene* hallTrigger = new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(MIDDLE_WIDTH, WALL_OFFSET + TRIGGER_OFFSET), new Collision(32, 32, Collision::ColliderType::Overlap), _SScene, new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET));
	
	Mirror* mirror{ new Mirror(MMirror.name, App::CreateSprite(MMirror.model, 6, 1, MMirror.frame, MMirror.scale), new Vector2D(250,250), new Collision(32, 32)) };
		mirror->SetMobility(Mobility::MOVABLE);

	MirrorShard* shard1{ new MirrorShard(MMirrorShard.name + "1", App::CreateSprite(MPage.model , 1, 1), new Vector2D(150,300), new Collision(32, 32)) };
	
	MirrorShard* shard2{ new MirrorShard(MMirrorShard.name + "2", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150,350), new Collision(32, 32)) };
	
	MirrorShard* shard3{ new MirrorShard(MMirrorShard.name + "3", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150,400), new Collision(32, 32)) };
	
	MirrorShard* shard4{ new MirrorShard(MMirrorShard.name + "4", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150, 450), new Collision(32, 32)) };
	
	ObjectController* objectC{ new ObjectController() };
	Character* character{ new Character(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), new Vector2D(350,250), new Collision(32, 32), 0, 4, objectC) };
	character->SetMobility(Mobility::MOVABLE);
	
	/*Start Puzzle*/
	_mirrorPuzzle->_mirror = mirror;
	_mirrorPuzzle->StartPuzzle();

	return false;
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
