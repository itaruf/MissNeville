#include "../stdafx.h"
#include "Lounge.h"

Lounge::Lounge(int ID) : Scene(ID)
{
}

Lounge::~Lounge()
{
	if (_dodgePuzzle)
		delete _dodgePuzzle;
}

void Lounge::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);

	/*std::cout << StateMain::_player->GetPosition()->_x << std::endl;*/

	ObjectController* objectC{new ObjectController() };

	StateMain::_player->SetPosition(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 128, MIDDLE_HEIGHT);

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(LOUNGE_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LOUNGE_WALL, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, LOUNGE_WALL), new Collision(2, MIDDLE_WIDTH + LOUNGE_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(2, MIDDLE_WIDTH + LOUNGE_WALL * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LOUNGE_WALL, 2)) };
	wallRight->SetTag("wall");

	/*PAGE*/
	auto page{ new Page(MPage.name + " 3" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(LOUNGE_WALL + 64, MIDDLE_HEIGHT), new Collision(16, 16), 0, DPage.p3) };

	/*Open the entrance door*/
	auto it = std::find_if(StateMain::_rooms[1]->GetActors().begin(), StateMain::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateMain::_rooms[1]->_SScene; });

	if (it != StateMain::_rooms[1]->GetActors().end())
		page->_onCollected += [this, it]() {dynamic_cast<TriggerScene*>(*it)->OnActivation(); };

	/*Weapons*/
	auto weapon{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 128, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 32), new Collision(16, 16), 0, 2, objectC) };
	weapon->SetTag("lethal");
	weapon->SetDirection(Direction::DOWN);

	auto weapon2{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 4, MKnife.frame, MKnife.scale), new Vector2D(MIDDLE_WIDTH - LOUNGE_WALL, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 32), new Collision(16, 16), 0, 2, objectC) };
	weapon2->SetTag("lethal");
	weapon2->SetDirection(Direction::UP);

	auto weapon3{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 4, MKnife.frame, MKnife.scale), new Vector2D(LOUNGE_WALL + 128, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 32), new Collision(16, 16), 0, 2, objectC) };
	weapon3->SetTag("lethal");
	weapon3->SetDirection(Direction::DOWN);

	auto oven{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(LOUNGE_WALL + 32, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 16), new Collision(92, 32)) };
	auto oven2{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 16), new Collision(92, 32)) };

	auto barrel{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 64, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 32), new Collision(32, 32)) };
	auto barrel2{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 64, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 32), new Collision(32, 32)) };

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(HALL_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _EScene) };
	}

void Lounge::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Lounge::Render()
{
	Scene::Render();
}

void Lounge::Exit()
{
}

bool Lounge::IsRoomCleared()
{
	if (!_dodgePuzzle)
		return false;

	if (!_dodgePuzzle->IsCleared())
		return false;

	else if (_dodgePuzzle->_status == Puzzle::Status::CLEARED)
		return true;

	else if (_dodgePuzzle->_status == Puzzle::Status::PENDING)
	{
		auto it = std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Ms. Smith"; });
		if (it != _actors.end())
		{
			RemoveActor(*it);
		}

		auto npc = std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == "Charlotte"; });
		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}

		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

		/*if (!stateDialogue)
			return true;

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_unlocked);
		StateMain::SetState(State::DIALOGUE);

		CSimpleSound::GetInstance().PlaySoundW(SFX.door_open, 0);*/

		_dodgePuzzle->_status = Puzzle::Status::CLEARED;
		return true;
	}
}
