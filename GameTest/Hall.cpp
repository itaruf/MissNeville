#include "stdafx.h"
#include "Hall.h"
#include "Models.h"

Hall::Hall(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Hall::Hall(int ID) : Scene(ID)
{
}

Hall::~Hall()
{
}

bool Hall::Init()
{
	if (Scene::Init())
		return true;

	_mirrorPuzzle = new MirrorPuzzle(MirrorPuzzle::Status::PENDING);

	// Triggers
	TriggerScene* entranceTrigger{ new TriggerScene("Entrance Trigger", App::CreateSprite(".\\TestData\\Icons\\question-mark.bmp", 1, 1), new Vector2D(APP_VIRTUAL_WIDTH / 2, WALL_OFFSET + TRIGGER_OFFSET), new Collision(16, 16, Collision::ColliderType::Overlap), _SScene, new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET)) };
	entranceTrigger->GetSprite()->SetFrame(2);
	entranceTrigger->GetSprite()->SetScale(1);
	AddActor(entranceTrigger);

	Mirror* mirror{ new Mirror("Mirror", App::CreateSprite(".\\TestData\\Props\\mirror.bmp", 2, 1), new Vector2D(250,250), new Collision(16, 16)) };
	mirror->GetSprite()->SetFrame(1);
	mirror->GetSprite()->SetScale(0.25);
	AddActor(mirror);
	mirror->SetMobility(Mobility::MOVABLE);

	MirrorShard* shard1{ new MirrorShard("Shard 1", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(150,300), new Collision(16, 16)) };
	shard1->GetSprite()->SetFrame(0);
	shard1->GetSprite()->SetScale(1);
	AddActor(shard1);

	MirrorShard* shard2{ new MirrorShard("Shard 2", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(150,350), new Collision(16, 16)) };
	shard1->GetSprite()->SetFrame(0);
	shard1->GetSprite()->SetScale(1);
	AddActor(shard2);

	MirrorShard* shard3{ new MirrorShard("Shard 3", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(150,400), new Collision(16, 16)) };
	shard1->GetSprite()->SetFrame(0);
	shard1->GetSprite()->SetScale(1);
	AddActor(shard3);

	MirrorShard* shard4{ new MirrorShard("Shard 4", App::CreateSprite(".\\TestData\\Props\\page.bmp", 1, 1), new Vector2D(150, 450), new Collision(16, 16)) };
	shard1->GetSprite()->SetFrame(0);
	shard1->GetSprite()->SetScale(1);
	AddActor(shard4);

	ObjectController* objectC{ new ObjectController() };
	Character* character{new Character("test",  App::CreateSprite(".\\TestData\\Props\\mirror.bmp", 2, 1), new Vector2D(350,250), new Collision(16, 16), 0, 4, objectC)};
	character->SetMobility(Mobility::MOVABLE);
	character->GetSprite()->SetFrame(1);
	character->GetSprite()->SetScale(0.25);
	AddActor(character);

	/*Start Puzzle*/
	_mirrorPuzzle->_mirror = mirror;
	_mirrorPuzzle->StartPuzzle();

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
	if (!_mirrorPuzzle)
		return false;

	if (!_mirrorPuzzle->IsCleared())
		return false;

	else if (_mirrorPuzzle->_status == Puzzle::Status::CLEARED)
		return true;

	else if (_mirrorPuzzle->_status == Puzzle::Status::PENDING)
	{
		std::string description = "No";

		auto page = new Page("Page 2", App::CreateSprite(MPage::model, 1, 1, MPage::frame, MPage::scale), new Vector2D(512, 394), new Collision(8, 8), 0, description);
		AddActor(page);

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

	return false; 
}
