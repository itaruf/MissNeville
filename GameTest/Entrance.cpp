#include "../stdafx.h"
#include "Entrance.h"

Entrance::Entrance(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Entrance::Entrance(int ID) : Scene(ID)
{
}

Entrance::~Entrance()
{
}

bool Entrance::Init()
{
	if (Scene::Init())
		return true;

	_mirrorPuzzle = new MirrorPuzzle(MirrorPuzzle::Status::PENDING);

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(16, 16, Collision::ColliderType::Overlap), _NScene, new Vector2D(APP_VIRTUAL_WIDTH / 2, WALL_OFFSET + TRIGGER_OFFSET + NEW_PLAYER_POS_OFFSET)) };
	AddActor(hallTrigger);

	Mirror* mirror{ new Mirror(MMirror.name, App::CreateSprite(MMirror.model, 6, 1, MMirror.frame, MMirror.scale), new Vector2D(250,250), new Collision(16, 16)) };
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_BROKEN, 1.0f / 15.0f, { 0,1,2,3,4,5 });
	mirror->GetSprite()->CreateAnimation(mirror->GetSprite()->ANIM_MIRROR_REPAIRED, 1.0f / 15.0f, { 5,4,3,2,1,0 });
	AddActor(mirror);
	mirror->SetMobility(Mobility::MOVABLE);

	TriggerAnimation* m{ new TriggerAnimation(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET - 200), new Collision(16, 16, Collision::ColliderType::Overlap)) };
	m->_anim = mirror->GetSprite()->ANIM_MIRROR_BROKEN;
	m->_targetSprite = mirror->GetSprite();
	m->_sfx = SFX.mirror_repaired;
	AddActor(m);

	MirrorShard* shard1{ new MirrorShard(MMirrorShard.name + "1", App::CreateSprite(MPage.model , 1, 1), new Vector2D(150,300), new Collision(16, 16)) };
	AddActor(shard1);

	MirrorShard* shard2{ new MirrorShard(MMirrorShard.name + "2", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150,350), new Collision(16, 16))};
	AddActor(shard2);

	MirrorShard* shard3{ new MirrorShard(MMirrorShard.name + "3", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150,400), new Collision(16, 16)) };
	AddActor(shard3);

	MirrorShard* shard4{ new MirrorShard(MMirrorShard.name + "4", App::CreateSprite(MPage.model, 1, 1), new Vector2D(150, 450), new Collision(16, 16))};
	AddActor(shard4);

	ObjectController* objectC{ new ObjectController() };
	Character* character{new Character(MTable.name, App::CreateSprite(MTable.model, 1, 1, MTable.frame, MTable.scale), new Vector2D(350,250), new Collision(16, 16), 0, 4, objectC)};
	character->SetMobility(Mobility::MOVABLE);
	AddActor(character);

	/*Start Puzzle*/
	_mirrorPuzzle->_mirror = mirror;
	_mirrorPuzzle->StartPuzzle();

	return false;
}

void Entrance::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B))
	{
		_mirrorPuzzle->_mirror->GetSprite()->SetAnimation(_mirrorPuzzle->_mirror->GetSprite()->ANIM_MIRROR_BROKEN);
		auto tmp = _mirrorPuzzle->_mirror->GetSprite()->GetAnimations()[_mirrorPuzzle->_mirror->GetSprite()->GetCurrentAnim()].m_frames;
		if (tmp[_mirrorPuzzle->_mirror->GetSprite()->GetFrame()] == tmp[tmp.size() - 1])
			_mirrorPuzzle->_mirror->GetSprite()->SetAnimation(-1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X))
	{
		_mirrorPuzzle->_mirror->GetSprite()->SetAnimation(_mirrorPuzzle->_mirror->GetSprite()->ANIM_MIRROR_REPAIRED);
		auto tmp = _mirrorPuzzle->_mirror->GetSprite()->GetAnimations()[_mirrorPuzzle->_mirror->GetSprite()->GetCurrentAnim()].m_frames;
		if (tmp[_mirrorPuzzle->_mirror->GetSprite()->GetFrame()] == tmp[tmp.size() - 1])
		{
			std::cout << true << std::endl;
			_mirrorPuzzle->_mirror->GetSprite()->SetAnimation(-1);
		}
	}
}

void Entrance::Render()
{
	Scene::Render();
}

bool Entrance::IsRoomCleared()
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

		auto page{ new Page(MPage.name + " 2" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(512, 394), new Collision(8, 8), 0, description)};
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
