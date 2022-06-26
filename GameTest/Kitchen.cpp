#include "../stdafx.h"
#include "Kitchen.h"

Kitchen::Kitchen(int ID) : Scene(ID)
{
}

Kitchen::Kitchen(int ID, DodgePuzzle* puzzle) : Scene(ID), _dodgePuzzle(puzzle)
{
}

Kitchen::~Kitchen()
{
	if (_dodgePuzzle)
		delete _dodgePuzzle;
}

void Kitchen::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);

	std::random_device myRandomDevice;
	/*std::cout << StateMain::_player->GetPosition()->_x << std::endl;*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - KITCHEN_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - KITCHEN_WALL * 2) / 32; i++)
		{
			unsigned seed = myRandomDevice();
			std::default_random_engine myRandomEngine(seed);

			if (seed % 10 == 0)
				new Actor(MBackground.name, App::CreateSprite(MBackground.model3, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(KITCHEN_WALL + 16 + i * 32, KITCHEN_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
			else
				new Actor(MBackground.name, App::CreateSprite(MBackground.model2, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(KITCHEN_WALL + 16 + i * 32, KITCHEN_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	StateMain::_player->SetPosition(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 128, MIDDLE_HEIGHT);
	_startingPos = new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 48, MIDDLE_HEIGHT);

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(KITCHEN_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - KITCHEN_WALL * 2, 2)) };
	wallLeft->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL, MIDDLE_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT - KITCHEN_WALL * 2, 2)) };
	wallRight->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, KITCHEN_WALL), new Collision(2, APP_VIRTUAL_WIDTH - KITCHEN_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(2, APP_VIRTUAL_WIDTH - KITCHEN_WALL * 2)) };
	wallTop->SetTag("wall");

	/*PAGE*/
	auto page{ new Page(MPage.name + " 3" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(KITCHEN_WALL + 16, MIDDLE_HEIGHT + 128), new Collision(16, 16), 0, DProps.p3) };

	_dodgePuzzle->_page = page;

	ObjectController* objectC{ new ObjectController() };
	_onCanOpenCell += [this, objectC]() {objectC->_activated = false; };

	/*Weapons*/

	auto weapon{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 1, MKnife.scale), new Vector2D(MIDDLE_WIDTH - 16, APP_VIRTUAL_HEIGHT - KITCHEN_WALL - 64), new Collision(32, 16, ColliderType::Overlap, new Vector2D(16, -16)), 0, 4, objectC) };
	weapon->SetTag("lethal");
	weapon->SetDirection(Direction::DOWN);

	auto weapon3{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 1, MKnife.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 512, APP_VIRTUAL_HEIGHT - KITCHEN_WALL - 64), new Collision(32, 16, ColliderType::Overlap, new Vector2D(16, -16)), 0, 4, objectC) };
	weapon3->SetTag("lethal");
	weapon3->SetDirection(Direction::DOWN);

	auto weapon2{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 1, MKnife.scale), new Vector2D(KITCHEN_WALL + 464, KITCHEN_WALL + 32), new Collision(32, 16, ColliderType::Overlap, new Vector2D(16, -16)), 0, 5, objectC) };
	weapon2->SetTag("lethal");
	weapon2->SetDirection(Direction::UP);

	auto weapon4{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 3, MKnife.scale), new Vector2D(KITCHEN_WALL + 32, MIDDLE_HEIGHT + 64), new Collision(16, 32, ColliderType::Overlap, new Vector2D(16, 0)), 0, 5, objectC) };
	weapon4->SetTag("lethal");
	weapon4->SetDirection(Direction::LEFT);

	auto weapon6{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 3, MKnife.scale), new Vector2D(KITCHEN_WALL + 32, MIDDLE_HEIGHT - 96), new Collision(16, 32, ColliderType::Overlap, new Vector2D(16, 0)), 0, 5, objectC) };
	weapon6->SetTag("lethal");
	weapon6->SetDirection(Direction::LEFT);

	auto weapon5{ new Character(MKnife.name, App::CreateSprite(MKnife.model, 3, 2, 3, MKnife.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 64, KITCHEN_WALL + 32), new Collision(16, 32, ColliderType::Overlap, new Vector2D(16, 0)), 0, 8, objectC) };
	weapon5->SetTag("lethal");
	weapon5->SetDirection(Direction::RIGHT);

	auto fire{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(KITCHEN_WALL + 64, MIDDLE_HEIGHT), new Collision(32,32, ColliderType::Overlap)) };
	fire->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire->SetTag("lethal");

	auto fire2{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(KITCHEN_WALL + 256, MIDDLE_HEIGHT - 128), new Collision(32,32, ColliderType::Overlap)) };
	fire2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire2->SetTag("lethal");

	auto fire3{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT - 64), new Collision(32,32, ColliderType::Overlap)) };
	fire3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire3->SetTag("lethal");

	auto fire4{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(MIDDLE_WIDTH + 128, MIDDLE_HEIGHT + 100), new Collision(32,32, ColliderType::Overlap)) };
	fire4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire4->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire4->SetTag("lethal");

	auto fire5{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(MIDDLE_WIDTH - 128,  MIDDLE_HEIGHT + 64), new Collision(32,32, ColliderType::Overlap)) };
	fire5->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire5->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire5->SetTag("lethal");

	auto fire6{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 100, MIDDLE_HEIGHT - 100), new Collision(32,32, ColliderType::Overlap)) };
	fire6->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire6->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire6->SetTag("lethal");

	auto fire7{ new Actor(MFire.name, App::CreateSprite(MFire.model, 12, 1, MFire.frame, MFire.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 144, MIDDLE_HEIGHT + 32), new Collision(32,32, ColliderType::Overlap)) };
	fire7->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_FIRE, 1 / 15.0f, { 0,1,2,3,4,5,6,7,8,9,10,11 }, true);
	fire7->GetSprite()->SetAnimation(CSimpleSprite::ANIM_FIRE);
	fire7->SetTag("lethal");

	/*Furnitures*/
	auto oven{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(KITCHEN_WALL + 32, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven->SetTag("wall");
	auto oven2{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven2->SetTag("wall");
	auto oven3{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven2->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven3->SetTag("wall");
	auto oven4{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven3->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven4->SetTag("wall");
	auto oven5{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven4->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven5->SetTag("wall");
	auto oven6{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven5->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven6->SetTag("wall");
	auto oven7{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven6->GetPosition()->_x + 96, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven7->SetTag("wall");
	auto oven8{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven7->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven8->SetTag("wall");
	auto oven9{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven8->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven9->SetTag("wall");
	auto oven10{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven9->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven10->SetTag("wall");
	auto oven11{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven10->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven11->SetTag("wall");
	auto oven12{ new Actor(MOven.name, App::CreateSprite(MOven.model, 1, 1, MOven.frame, MOven.scale), new Vector2D(oven11->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(92, 32)) }; oven12->SetTag("wall");

	auto cell{ new Actor(MCell.name, App::CreateSprite(MCell.model, 1, 1, MCell.frame, MCell.scale), new Vector2D(page->GetPosition()->_x, page->GetPosition()->_y + 32), new Collision(92, 32)) };

	// Remove the blocked way to the page
	_onCanOpenCell += [this, cell]() {RemoveActor(cell); };

	auto barrel{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 32, APP_VIRTUAL_HEIGHT - KITCHEN_WALL - 80), new Collision(32, 32)) };
	auto barrel2{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(KITCHEN_WALL + 32, KITCHEN_WALL + 16), new Collision(32, 32)) };
	auto barrel3{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(MIDDLE_WIDTH + 65, KITCHEN_WALL + 16), new Collision(32, 32)) };
	auto barrel4{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 32, MIDDLE_HEIGHT + 48), new Collision(32, 32)) };
	barrel4->SetTag("wall");
	auto barrel5{ new Actor(MBarrel.name, App::CreateSprite(MBarrel.model, 1, 1, MBarrel.frame, MBarrel.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 32, MIDDLE_HEIGHT - 96), new Collision(32, 32)) };
	barrel5->SetTag("wall");

	auto skull{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(KITCHEN_WALL + 32, KITCHEN_WALL + 128), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull2{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - 16, KITCHEN_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull3{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(MIDDLE_WIDTH - 44, MIDDLE_HEIGHT + 16), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull4{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(MIDDLE_WIDTH + 28, MIDDLE_HEIGHT + 100), new Collision(32, 32, ColliderType::Overlap)) };
	auto skull5{ new Actor(MSkull.name, App::CreateSprite(MSkull.model2, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(MIDDLE_WIDTH + 70, MIDDLE_HEIGHT - 80), new Collision(32, 32, ColliderType::Overlap)) };

	auto bag{ new Actor(MBag.name, App::CreateSprite(MBag.model, 1, 1, MBag.frame, MBag.scale), new Vector2D(barrel->GetPosition()->_x - 48, barrel->GetPosition()->_y), new Collision(32, 32, ColliderType::Overlap)) };
	auto bag2{ new Actor(MBag.name, App::CreateSprite(MBag.model, 1, 1, MBag.frame, MBag.scale), new Vector2D(barrel->GetPosition()->_x, barrel->GetPosition()->_y - 32), new Collision(32, 32, ColliderType::Overlap)) };

	/*Interruptors*/
	auto button{ new Button(MPot.name, App::CreateSprite(MPot.model, 5, 1, MPot.frame, MPot.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - KITCHEN_WALL), new Collision(32, 32), true)};
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

	auto button2{ new Button(MPot.name, App::CreateSprite(MPot.model, 5, 1, MPot.frame, MPot.scale), new Vector2D(KITCHEN_WALL, MIDDLE_HEIGHT - 96), new Collision(32, 32), true) };
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

	auto button3{ new Button(MPot.name, App::CreateSprite(MPot.model, 5, 1, MPot.frame, MPot.scale), new Vector2D(KITCHEN_WALL + 464, KITCHEN_WALL), new Collision(32, 32), true) };
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

	MirrorShard* shard3{ new MirrorShard(MMirrorShard.name + "3", App::CreateSprite(MPage.model , 1, 1), new Vector2D(page->GetPosition()->_x, page->GetPosition()->_y + 16), new Collision(32, 32)) };

	// Triggers
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MCarpet.model, 1, 1, MCarpet.frame, 0.8), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT),new Vector2D(HALL_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _EScene) };

	auto arrowRight{ new Actor(MArrow.name, App::CreateSprite(MArrow.right, 1, 1, MArrow.frame, MArrow.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL + 32, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap)) };

	/*NPC*/
	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, 4, MCharlotte.scale), new Vector2D(APP_VIRTUAL_WIDTH - KITCHEN_WALL - TRIGGER_OFFSET, MIDDLE_HEIGHT - 56), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.k1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.k2));
	charlotte->SetCurrentDialogue(0);

	auto anne{ new NPC("Anne Neville", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), new Vector2D(cell->GetPosition()->_x,cell->GetPosition()->_y - 96), new Collision(32, 32)) };
	anne->dialogues.insert(std::make_pair(0, DMother.k1));
	anne->SetCurrentDialogue(0);

	/*On Puzzle solved*/
	_dodgePuzzle->_onSolved += [this]() 
	{
		StateMain::_player->_footStep = new CSimpleSprite(MBlood.model); 

		for (auto& actor : StateMain::_rooms[1]->GetActors())
		{
			auto character{ dynamic_cast<Character*>(actor) };

			if (!character)
				continue;

			if (!character->GetController())
				continue;

			character->GetController()->_activated = true;
		}
	};

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(DDetective.k1);
	StateMain::SetState(State::DIALOGUE);
}

void Kitchen::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Kitchen::Render()
{
	Scene::Render();
}

void Kitchen::Exit()
{
}

bool Kitchen::IsRoomCleared()
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
		_dodgePuzzle->_onSolved();

		return true;
	}
}

// The cell can open only when all the interruptors are shutdown
bool Kitchen::CanOpenCell()
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
