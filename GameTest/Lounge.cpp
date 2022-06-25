#include "../stdafx.h"
#include "Lounge.h"

Lounge::Lounge(int ID) : Scene(ID)
{
}

Lounge::Lounge(int ID, DodgePuzzle* puzzle) : Scene(ID), _dodgePuzzle(puzzle)
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

	std::random_device myRandomDevice;
	/*std::cout << StateMain::_player->GetPosition()->_x << std::endl;*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - LOUNGE_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - LOUNGE_WALL * 2) / 32; i++)
		{
			unsigned seed = myRandomDevice();
			std::default_random_engine myRandomEngine(seed);

			if (seed % 10 == 0)
				new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(LOUNGE_WALL + 16 + i * 32, LOUNGE_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
			else
				new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(LOUNGE_WALL + 16 + i * 32, LOUNGE_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	StateMain::_player->SetPosition(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 128, MIDDLE_HEIGHT);
	_startingPos = new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 32, MIDDLE_HEIGHT);

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(LOUNGE_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - LOUNGE_WALL * 2, 2)) };
	wallLeft->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - LOUNGE_WALL * 2, 2)) };
	wallRight->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, LOUNGE_WALL), new Collision(2, APP_VIRTUAL_WIDTH - LOUNGE_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(2, APP_VIRTUAL_WIDTH - LOUNGE_WALL * 2)) };
	wallTop->SetTag("wall");

	/*PAGE*/
	auto page{ new Page(MPage.name + " 3" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(LOUNGE_WALL + 16, MIDDLE_HEIGHT + 128), new Collision(16, 16), 0, DPage.p3) };

	_dodgePuzzle->_page = page;

	/*Open the entrance door*/
	auto it = std::find_if(StateMain::_rooms[1]->GetActors().begin(), StateMain::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateMain::_rooms[1]->_SScene; });

	if (it != StateMain::_rooms[1]->GetActors().end())
		page->_onCollected += [this, it]() {dynamic_cast<TriggerScene*>(*it)->OnActivation(); };

	ObjectController* objectC{ new ObjectController() };
	_onCanOpenCell += [this, objectC]() {objectC->_activated = false; };

	/*Weapons*/
	/*auto weapon{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 1, MKnife.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 64), new Collision(16, 16, ColliderType::Overlap), 0, 4, objectC) };
	weapon->SetTag("lethal");
	weapon->SetDirection(Direction::DOWN);

	auto weapon3{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 512, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 64), new Collision(16, 16, ColliderType::Overlap), 0, 4, objectC) };
	weapon3->SetTag("lethal");
	weapon3->SetDirection(Direction::DOWN);

	auto weapon2{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(LOUNGE_WALL + 464, LOUNGE_WALL + 32), new Collision(16, 16, ColliderType::Overlap), 0, 5, objectC) };
	weapon2->SetTag("lethal");
	weapon2->SetDirection(Direction::UP);

	auto weapon4{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(LOUNGE_WALL + 32, MIDDLE_HEIGHT + 64), new Collision(16, 16, ColliderType::Overlap), 0, 5, objectC) };
	weapon4->SetTag("lethal");
	weapon4->SetDirection(Direction::LEFT);

	auto weapon6{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(LOUNGE_WALL + 32, MIDDLE_HEIGHT - 96), new Collision(16, 16, ColliderType::Overlap), 0, 5, objectC) };
	weapon6->SetTag("lethal");
	weapon6->SetDirection(Direction::LEFT);

	auto weapon5{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 2, MKnife.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 16, LOUNGE_WALL + 32), new Collision(16, 16, ColliderType::Overlap), 0, 8, objectC) };
	weapon5->SetTag("lethal");
	weapon5->SetDirection(Direction::RIGHT);

	auto fire{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(LOUNGE_WALL + 64, MIDDLE_HEIGHT), new Collision(32,32, ColliderType::Overlap)) };
	fire->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire->SetTag("lethal");

	auto fire2{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(LOUNGE_WALL + 256, MIDDLE_HEIGHT - 128), new Collision(32,32, ColliderType::Overlap)) };
	fire2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire2->SetTag("lethal");

	auto fire3{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT - 64), new Collision(32,32, ColliderType::Overlap)) };
	fire3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire3->SetTag("lethal");

	auto fire4{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(MIDDLE_WIDTH + 128, MIDDLE_HEIGHT + 100), new Collision(32,32, ColliderType::Overlap)) };
	fire4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire4->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire4->SetTag("lethal");

	auto fire5{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(MIDDLE_WIDTH - 128,  MIDDLE_HEIGHT + 64), new Collision(32,32, ColliderType::Overlap)) };
	fire5->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire5->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire5->SetTag("lethal");

	auto fire6{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 100, MIDDLE_HEIGHT - 100), new Collision(32,32, ColliderType::Overlap)) };
	fire6->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire6->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire6->SetTag("lethal");

	auto fire7{ new Actor(MFire.name, App::CreateSprite(MFire.model, 1, 4, MFire.frame, MFire.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 144, MIDDLE_HEIGHT + 32), new Collision(32,32, ColliderType::Overlap)) };
	fire7->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3 }, true);
	fire7->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire7->SetTag("lethal");*/

	/*Furnitures*/
	auto oven{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(LOUNGE_WALL + 32, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven2{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven3{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven2->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven4{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven3->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) }; 
	auto oven5{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven4->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) }; 
	auto oven6{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven5->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven7{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven6->GetPosition()->_x + 96, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven8{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven7->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven9{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven8->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven10{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven9->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven11{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven10->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };
	auto oven12{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven11->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(92, 32)) };

	auto cell{ new Actor(MCell.name, App::CreateSprite(MCell.model, 1, 1, MCell.frame, MCell.scale), new Vector2D(page->GetPosition()->_x, page->GetPosition()->_y + 32), new Collision(92, 32)) };

	// Remove the blocked way to the page
	_onCanOpenCell += [this, cell]() {RemoveActor(cell); };

	auto barrel{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 32, APP_VIRTUAL_HEIGHT - LOUNGE_WALL - 80), new Collision(32, 32)) };
	auto barre2{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(LOUNGE_WALL + 32, LOUNGE_WALL + 16), new Collision(32, 32)) };
	auto barre3{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(MIDDLE_WIDTH + 65, LOUNGE_WALL + 16), new Collision(32, 32)) };

	auto skull{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(LOUNGE_WALL + 32, LOUNGE_WALL + 128), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull2{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - 16, LOUNGE_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull3{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(MIDDLE_WIDTH - 44, MIDDLE_HEIGHT + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull4{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(MIDDLE_WIDTH + 28, MIDDLE_HEIGHT + 100), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull5{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(MIDDLE_WIDTH + 70, MIDDLE_HEIGHT - 80), new Collision(32, 32, ColliderType::Overlap)) };

	auto bag{ new Actor(MBag.name, App::CreateSprite(MBag.model, 1, 1, MBag.frame, MBag.scale), new Vector2D(barrel->GetPosition()->_x - 48, barrel->GetPosition()->_y), new Collision(32, 32, ColliderType::Overlap)) };
	auto bag2{ new Actor(MBag.name, App::CreateSprite(MBag.model, 1, 1, MBag.frame, MBag.scale), new Vector2D(barrel->GetPosition()->_x, barrel->GetPosition()->_y - 32), new Collision(32, 32, ColliderType::Overlap)) };

	/*Interruptors*/
	auto button{ new Button(MPot.name, App::CreateSprite(MPot.model, 5, 1, MPot.frame, MPot.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LOUNGE_WALL), new Collision(32, 32), true)};
	button->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOIL, 1 / 5.0f, { 1,2,3,4 }, true);
	button->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOIL);

	button->_onActivated += [this, button]()
	{
		button->GetSprite()->SetAnimation(-1);
		button->GetSprite()->SetFrame(0);
		button->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOIL);
	};
	button->_onDeactivated += [this, button]()
	{
		CanOpenCell();
		button->GetSprite()->SetAnimation(-1);
		button->GetSprite()->SetFrame(0);
	};

	auto button2{ new Button(MPot.name, App::CreateSprite(MPot.model, 5, 1, MPot.frame, MPot.scale), new Vector2D(LOUNGE_WALL, MIDDLE_HEIGHT - 96), new Collision(32, 32), true) };
	button2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOIL, 1 / 5.0f, { 1,2,3,4 }, true);
	button2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOIL);

	button2->_onActivated += [this, button2]()
	{
		button2->GetSprite()->SetAnimation(-1);
		button2->GetSprite()->SetFrame(0);
		button2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOIL);
	};
	button2->_onDeactivated += [this, button2]()
	{
		CanOpenCell();
		button2->GetSprite()->SetAnimation(-1);
		button2->GetSprite()->SetFrame(0);
	};

	auto button3{ new Button(MPot.name, App::CreateSprite(MPot.model, 5, 1, MPot.frame, MPot.scale), new Vector2D(LOUNGE_WALL + 464, LOUNGE_WALL), new Collision(32, 32), true) };
	button3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOIL, 1 / 5.0f, { 1,2,3,4 }, true);
	button3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOIL);

	button3->_onActivated += [this, button3]()
	{
		button3->GetSprite()->SetAnimation(-1);
		button3->GetSprite()->SetFrame(0);
		button3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOIL);
	};
	button3->_onDeactivated += [this, button3]()
	{
		CanOpenCell();
		button3->GetSprite()->SetAnimation(-1);
		button3->GetSprite()->SetFrame(0);
	};

	_buttons.emplace_back(button);
	_buttons.emplace_back(button2);
	_buttons.emplace_back(button3);

	MirrorShard* shard3{ new MirrorShard(MMirrorShard.name + "3", App::CreateSprite(MPage.model , 1, 1), new Vector2D(page->GetPosition()->_x, page->GetPosition()->_y + 32), new Collision(32, 32)) };

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(HALL_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _EScene) };

	/*NPC*/
	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, 4, MCharlotte.scale), new Vector2D(APP_VIRTUAL_WIDTH - LOUNGE_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT - 56), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.k1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.k2));
	charlotte->SetCurrentDialogue(0);

	auto anne{ new NPC("Anne Neville", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), new Vector2D(cell->GetPosition()->_x,cell->GetPosition()->_y - 64), new Collision(32, 32)) };
	anne->dialogues.insert(std::make_pair(0, DMother.k1));
	anne->SetCurrentDialogue(0);


	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(DDetective.k1);
	StateMain::SetState(State::DIALOGUE);
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

	else if (_dodgePuzzle->_status == Status::CLEARED)
		return true;

	else if (_dodgePuzzle->_status == Status::PENDING)
	{
		auto it = std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Anne Neville"; });
		if (it != _actors.end())
		{
			CSimpleSound::GetInstance().PlaySoundW((*it)->_SInteract, 0);
			RemoveActor(*it);
		}

		auto npc = std::find_if(_actors.begin(), _actors.end(), [](Actor* npc) { return npc->GetName() == MCharlotte.name; });
		if (npc != _actors.end())
		{
			dynamic_cast<NPC*>(*npc)->SetCurrentDialogue(1);
		}

		auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

		if (!stateDialogue)
			return true;

		stateDialogue->_currentDialogue.emplace_back(DDetective.k2);

		StateMain::SetState(State::DIALOGUE);

		_dodgePuzzle->_status = Status::CLEARED;
		return true;
	}
}

// The cell can open only when all the interruptors are shutdown
bool Lounge::CanOpenCell()
{
	for (const auto& button : _buttons)
	{
		if (button->isActivated())
			return false;
	}

	// The cell can open
	for (const auto& button : _buttons)
	{
		button->_onActivated.funcs.clear();
		button->_onDeactivated.funcs.clear();
	}
	_onCanOpenCell();
	return true;
}
