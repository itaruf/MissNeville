#include "../stdafx.h"
#include "Library.h"

Library::Library(int ID) : Scene(ID)
{
}

Library::Library(int ID, TPPuzzle* puzzle) : Scene(ID), _TPPuzzle(puzzle)
{
}

Library::~Library()
{
	if (_TPPuzzle)
		delete _TPPuzzle;
}

void Library::Init()
{
	if (initialized)
		return;

	Scene::Init();
	AddActor(StateMain::_player);

	/*Background First*/
	for (int j = 0; j < (APP_VIRTUAL_HEIGHT - LIBRARY_WALL * 2) / 32; j++)
	{
		for (int i = 0; i < (APP_VIRTUAL_WIDTH - LIBRARY_WALL * 2) / 32; i++)
		{
			new Actor(MBackground.name, App::CreateSprite(MBackground.model, 1, 1, MBackground.frame, MBackground.scale), new Vector2D(LIBRARY_WALL + 16 + i * 32, LIBRARY_WALL + 16 + j * 32), new Collision(32, 32, ColliderType::Overlap));
		}
	}

	auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(LIBRARY_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LIBRARY_WALL, 2)) };
	wallLeft->SetTag("wall");

	auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, LIBRARY_WALL), new Collision(2, MIDDLE_WIDTH + LIBRARY_WALL * 2)) };
	wallBot->SetTag("wall");

	auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, APP_VIRTUAL_HEIGHT - LIBRARY_WALL), new Collision(2, MIDDLE_WIDTH + LIBRARY_WALL * 2)) };
	wallTop->SetTag("wall");

	auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - LIBRARY_WALL, MIDDLE_HEIGHT), new Collision(MIDDLE_HEIGHT + LIBRARY_WALL, 2)) };
	wallRight->SetTag("wall");

	/*PAGE*/
	auto page{ new Page(MPage.name + " 2" , App::CreateSprite(MPage.model, 1, 1, MPage.frame, MPage.scale), new Vector2D(), new Collision(16, 16), 0, DProps.p2) };

	/*Open the Kitchen door*/
	auto it = std::find_if(StateMain::_rooms[1]->GetActors().begin(), StateMain::_rooms[1]->GetActors().end(), [](Actor* actor) { if (dynamic_cast<TriggerScene*>(actor)) return dynamic_cast<TriggerScene*>(actor)->_scene == StateMain::_rooms[1]->_WScene; });

	if (it != StateMain::_rooms[1]->GetActors().end())
		page->_onCollected += [this, it]() {dynamic_cast<TriggerScene*>(*it)->OnActivation(); };

	/*Initiating Puzzles*/
	_TPPuzzle->_page = page;

	ObjectController* objectC{ new ObjectController() };

	_startingPos = new Vector2D(LIBRARY_WALL + TRIGGER_OFFSET + NEW_PLAYER_POS, MIDDLE_HEIGHT);
	/*_startingPos = new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT - 32);*/
	
	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(LIBRARY_WALL + TRIGGER_OFFSET, MIDDLE_HEIGHT), new Vector2D(APP_VIRTUAL_WIDTH - HALL_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap), _WScene) };
	
	auto arrowLeft{ new Actor(MArrow.name, App::CreateSprite(MArrow.left, 1, 1, MArrow.frame, MArrow.scale), new Vector2D(LIBRARY_WALL  - 32, MIDDLE_HEIGHT), new Collision(32, 32, ColliderType::Overlap)) };

	auto wallH2{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, (MIDDLE_HEIGHT + 64)), new Collision(2, MIDDLE_WIDTH + LIBRARY_WALL * 2)) };
	wallH2->SetTag("wall");
	
	auto wallV2{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH - 128, wallH2->GetPosition()->_y / 2 + 64), new Collision(MIDDLE_HEIGHT / 2 + LIBRARY_WALL, 2)) };
	wallV2->SetTag("wall");
	
	auto wallV3{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(wallV2->GetPosition()->_x + 256, wallH2->GetPosition()->_y / 2 + 64), new Collision(MIDDLE_HEIGHT / 2 + LIBRARY_WALL, 2)) };
	wallV3->SetTag("wall");
	
	auto wallV4{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, wallH2->GetPosition()->_y + 100), new Collision(MIDDLE_HEIGHT - LIBRARY_WALL * 2 + 64, 2)) };
	wallV4->SetTag("wall");
	
	/* Triggers*/
	
	// First Part
	TriggerScene* tp1{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 100), _startingPos)};
	tp1->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp1->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp1->_SInteract = SFX.tp_sound;

	TriggerScene* tp2{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 200), new Vector2D(wallV4->GetPosition()->_x + 128,  wallH2->GetPosition()->_y + 128))};
	tp2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp2->_SInteract = SFX.tp_sound;

	// Second Part
	TriggerScene* tp3{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV4->GetPosition()->_x + 256,  wallH2->GetPosition()->_y + 126), new Vector2D(APP_VIRTUAL_WIDTH - LIBRARY_WALL - TRIGGER_OFFSET - NEW_PLAYER_POS, MIDDLE_HEIGHT)) };
	tp3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp3->_SInteract = SFX.tp_sound;

	TriggerScene* tp4{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV4->GetPosition()->_x + 256,  wallH2->GetPosition()->_y + 32),  _startingPos) };
	tp4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp4->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp4->_SInteract = SFX.tp_sound;

	TriggerScene* tp5{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV4->GetPosition()->_x + 128,  wallH2->GetPosition()->_y + 32),  _startingPos) };
	tp5->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp5->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp5->_SInteract = SFX.tp_sound;

	// Third Part
	TriggerScene* tp6{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV3->GetPosition()->_x + 128,  wallH2->GetPosition()->_y - 100), _startingPos) };
	tp6->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp6->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp6->_SInteract = SFX.tp_sound;

	TriggerScene* tp7{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV3->GetPosition()->_x + 128,  wallH2->GetPosition()->_y - 200), new Vector2D(wallV2->GetPosition()->_x - 72, wallH2->GetPosition()->_y + 64)) };
	tp7->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp7->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp7->_SInteract = SFX.tp_sound;

	// Fourth Part
	TriggerScene* tp8{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV2->GetPosition()->_x - 200, wallH2->GetPosition()->_y + 96), _startingPos) };
	tp8->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp8->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp8->_SInteract = SFX.tp_sound;

	TriggerScene* tp9{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV2->GetPosition()->_x , wallH2->GetPosition()->_y + 96), new Vector2D(MIDDLE_WIDTH , MIDDLE_HEIGHT - 32)) };
	tp9->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp9->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp9->_SInteract = SFX.tp_sound;

	TriggerScene* tp10{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(wallV2->GetPosition()->_x , wallH2->GetPosition()->_y + 32), _startingPos) };
	tp10->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp10->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp10->_SInteract = SFX.tp_sound;

	// Fifth Part 
	TriggerScene* tp11{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MPentagramme.model, 4, 4, MPentagramme.frame, MPentagramme.scale), new Vector2D(MIDDLE_WIDTH , MIDDLE_HEIGHT - 128),  _startingPos)};
	tp11->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_PENTAGRAMME, 1 / 15.0f, { 5, 6, 7, 8, 9, 10, 11, 12 }, true);
	tp11->GetSprite()->SetAnimation(CSimpleSprite::ANIM_PENTAGRAMME);
	tp11->_SInteract = SFX.tp_sound;

	/****PROPS*****/
	/*First Part*/
	auto commode{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH - 128, wallH2->GetPosition()->_y - 64), new Collision(64, 32)) };
	commode->SetTag("wall");
	auto commode2{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH - 128, commode->GetPosition()->_y - 92), new Collision(64, 32)) };
	commode->SetTag("wall");
	auto commode3{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH - 128, commode2->GetPosition()->_y - 92), new Collision(64, 32)) };
	commode->SetTag("wall");

	auto shelf8{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(LIBRARY_WALL + 24, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };	
	auto shelf9{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf8->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };	
	auto shelf10{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf9->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf11{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf10->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf12{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf11->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf13{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf12->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf14{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf13->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto papers{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(LIBRARY_WALL + 24, wallH2->GetPosition()->_y - 128), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers2{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(LIBRARY_WALL + 50, wallH2->GetPosition()->_y - 200), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers3{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(LIBRARY_WALL + 100, wallH2->GetPosition()->_y - 300), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers4{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(LIBRARY_WALL + 150, wallH2->GetPosition()->_y - 250), new Collision(32, 32, ColliderType::Overlap)) };
	
	auto web{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(LIBRARY_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 80), new Collision(32, 32, ColliderType::Overlap)) };
	auto web2{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - LIBRARY_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web3{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(LIBRARY_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 144), new Collision(32, 32, ColliderType::Overlap)) };
	auto web4{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - LIBRARY_WALL - 48, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 176), new Collision(32, 32, ColliderType::Overlap)) };
	auto web5{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(LIBRARY_WALL + 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 208), new Collision(32, 32, ColliderType::Overlap)) };
	auto web6{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - LIBRARY_WALL - 16, APP_VIRTUAL_HEIGHT - ENTRANCE_WALL - 240), new Collision(32, 32, ColliderType::Overlap)) };
	auto web7{ new Actor(MWeb.name, App::CreateSprite(MWeb.model, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(LIBRARY_WALL + 16, ENTRANCE_WALL + 48), new Collision(32, 32, ColliderType::Overlap)) };
	auto web8{ new Actor(MWeb.name, App::CreateSprite(MWeb.model2, 1, 1, MWeb.frame, MWeb.scale), new Vector2D(APP_VIRTUAL_WIDTH - LIBRARY_WALL - 16, ENTRANCE_WALL + 16), new Collision(32, 32, ColliderType::Overlap)) };

	auto blood{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), new Vector2D(MIDDLE_WIDTH - 64, MIDDLE_HEIGHT - 64), new Collision(32, 32, ColliderType::Overlap)) };
	auto blood2{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 1, MBlood.frame, MBlood.scale2), new Vector2D(MIDDLE_WIDTH + 200, MIDDLE_HEIGHT - 200), new Collision(32, 32, ColliderType::Overlap)) };

	auto table5{ new Character(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(LIBRARY_WALL + 32, wallH2->GetPosition()->_y - 150), new Collision(32, 32), 0, 2, objectC) };
	table5->SetDirection(Direction::RIGHT);
	auto table6{ new Character(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(LIBRARY_WALL + 164, wallH2->GetPosition()->_y - 250), new Collision(32, 32), 0, 2, objectC) };
	table6->SetDirection(Direction::LEFT);

	auto book{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, MBook.frame, MBook.scale), new Vector2D(LIBRARY_WALL + 92, wallH2->GetPosition()->_y - 92), new Collision(32, 32)) };
	book->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 12, 13, 14, 15, 16, 17 }, true);
	book->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	/*Second Part*/
	auto commode7{ new Actor(MShelf.name, App::CreateSprite(MCommode.model6, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH, wallH2->GetPosition()->_y + 46), new Collision(64, 32)) };
	auto commode8{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH, commode7->GetPosition()->_y + 92), new Collision(64, 32)) };

	auto shelf28{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(wallV4->GetPosition()->_x + 96, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf29{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf28->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf30{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf29->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf31{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf30->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf32{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf31->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf33{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf32->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf34{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf33->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf35{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf34->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf36{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf35->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto papers5{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf28->GetPosition()->_x + 24, wallH2->GetPosition()->_y + 10), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers6{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf28->GetPosition()->_x - 50, wallH2->GetPosition()->_y + 110), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers7{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf28->GetPosition()->_x + 100, wallH2->GetPosition()->_y + 90), new Collision(32, 32, ColliderType::Overlap)) };

	auto skull3{ new Actor(MSkull.name, App::CreateSprite(MSkull.model, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(shelf30->GetPosition()->_x + 200, wallH2->GetPosition()->_y + 20), new Collision(32, 32)) };
	auto skull4{ new Actor(MSkull.name, App::CreateSprite(MSkull.model, 1, 1, MSkull.frame, MSkull.scale), new Vector2D(shelf30->GetPosition()->_x + 100, wallH2->GetPosition()->_y + 164), new Collision(32, 32)) };

	auto book2{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, 24, MBook.scale), new Vector2D(shelf28->GetPosition()->_x - 32, wallH2->GetPosition()->_y + 64), new Collision(32, 32)) };
	book2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 24, 25, 26, 27, 28, 29 }, true);
	book2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	auto book3{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, 24, MBook.scale), new Vector2D(shelf33->GetPosition()->_x + 40, wallH2->GetPosition()->_y + 92), new Collision(32, 32)) };
	book3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 24, 25, 26, 27, 28, 29 }, true);
	book3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	auto table7{ new Character(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(shelf28->GetPosition()->_x + 100, wallH2->GetPosition()->_y + 90), new Collision(32, 32), 0, 2, objectC) };
	table7->SetDirection(Direction::DOWN);

	/*Third Part*/
	auto shelf21{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(wallV3->GetPosition()->_x + 40, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf22{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf21->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf23{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf22->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf24{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf23->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf25{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf24->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf26{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf25->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf27{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf26->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto papers8{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf21->GetPosition()->_x + 24, wallH2->GetPosition()->_y - 100), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers9{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf23->GetPosition()->_x + 50, wallH2->GetPosition()->_y - 150), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers10{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf24->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 290), new Collision(32, 32, ColliderType::Overlap)) };

	auto book4{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, 24, MBook.scale), new Vector2D(shelf23->GetPosition()->_x - 32, wallH2->GetPosition()->_y - 64), new Collision(32, 32)) };
	book4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 24, 25, 26, 27, 28, 29 }, true);
	book4->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	auto book5{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, 24, MBook.scale), new Vector2D(shelf35->GetPosition()->_x + 40, wallH2->GetPosition()->_y - 200), new Collision(32, 32)) };
	book5->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 24, 25, 26, 27, 28, 29 }, true);
	book5->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	auto table8{ new Character(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(shelf25->GetPosition()->_x, wallH2->GetPosition()->_y - 160), new Collision(32, 32), 0, 3, objectC) };
	table8->SetDirection(Direction::LEFT);

	/*Fourth Part*/
	auto shelf{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(LIBRARY_WALL + 24, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf2{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf3{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf2->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf4{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf3->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf5{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf4->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf6{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf5->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf7{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf6->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf37{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf7->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf38{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf37->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf39{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf38->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };
	auto shelf40{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf39->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - LIBRARY_WALL - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto book6{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, 24, MBook.scale), new Vector2D(shelf2->GetPosition()->_x - 32, wallH2->GetPosition()->_y + 64), new Collision(32, 32)) };
	book6->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 24, 25, 26, 27, 28, 29 }, true);
	book6->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	auto book7{ new Actor(MBook.name, App::CreateSprite(MBook.model, 6, 7, 24, MBook.scale), new Vector2D(shelf37->GetPosition()->_x + 60, wallH2->GetPosition()->_y + 92), new Collision(32, 32)) };
	book7->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BOOK_OPENING, 1 / 15.0f, { 24, 25, 26, 27, 28, 29 }, true);
	book7->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BOOK_OPENING);

	auto table9{ new Character(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(LIBRARY_WALL + 140, wallH2->GetPosition()->_y + 32), new Collision(32, 32), 0, 4, objectC) };
	table9->SetDirection(Direction::UP);

	auto papers11{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf->GetPosition()->_x + 24, wallH2->GetPosition()->_y + 50), new Collision(32, 32, ColliderType::Overlap)) };
	auto papers12{ new Actor(MPage.name, App::CreateSprite(MPage.model2, 1, 1, MPage.frame, MPage.scale2), new Vector2D(shelf4->GetPosition()->_x + 90, wallH2->GetPosition()->_y + 100), new Collision(32, 32, ColliderType::Overlap)) };

	/*Fifth Part*/
	auto commode4{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(wallV2->GetPosition()->_x + 256, wallH2->GetPosition()->_y - 64), new Collision(64, 32)) };
	auto commode5{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(wallV2->GetPosition()->_x + 256, commode4->GetPosition()->_y - 92), new Collision(64, 32)) };
	auto commode6{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(wallV2->GetPosition()->_x + 256, commode5->GetPosition()->_y - 92), new Collision(64, 32)) };
	
	auto shelf15{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(wallV2->GetPosition()->_x + 48, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf16{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf15->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf17{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf16->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf18{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf17->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf19{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf18->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	auto shelf20{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf19->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto table{ new Actor(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(tp11->GetPosition()->_x - 48, tp11->GetPosition()->_y), new Collision(32, 32)) };
	auto lamp{ new Actor(MLamp.name, App::CreateSprite(MLamp.model, 4, 1, 0, MLamp.scale), new Vector2D(table->GetPosition()->_x, table->GetPosition()->_y + 16), new Collision(32, 32)) };
	lamp->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_LAMP, 1 / 5.0f, { 0, 1, 2, 3 }, true);
	lamp->GetSprite()->SetAnimation(CSimpleSprite::ANIM_LAMP);

	auto table2{ new Actor(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(tp11->GetPosition()->_x + 48, tp11->GetPosition()->_y), new Collision(32, 32)) };
	auto lamp2{ new Actor(MLamp.name, App::CreateSprite(MLamp.model, 4, 1, 0, MLamp.scale),new Vector2D(table2->GetPosition()->_x, table2->GetPosition()->_y + 16), new Collision(32, 32)) };
	lamp2->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_LAMP, 1 / 5.0f, { 0, 1, 2, 3 }, true);
	lamp2->GetSprite()->SetAnimation(CSimpleSprite::ANIM_LAMP);

	auto table3{ new Actor(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(tp11->GetPosition()->_x, tp11->GetPosition()->_y + 32), new Collision(32, 32)) };
	auto lamp3{ new Actor(MLamp.name, App::CreateSprite(MLamp.model, 4, 1, 0, MLamp.scale), new Vector2D(table3->GetPosition()->_x, table3->GetPosition()->_y + 16), new Collision(32, 32)) };
	lamp3->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_LAMP, 1 / 5.0f, { 0, 1, 2, 3 }, true);
	lamp3->GetSprite()->SetAnimation(CSimpleSprite::ANIM_LAMP);

	auto table10{ new Actor(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(table->GetPosition()->_x + 16, table->GetPosition()->_y - 40), new Collision(32, 32)) };
	auto lamp4{ new Actor(MLamp.name, App::CreateSprite(MLamp.model, 4, 1, 0, MLamp.scale),new Vector2D(table10->GetPosition()->_x, table10->GetPosition()->_y + 16), new Collision(32, 32)) };
	lamp4->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_LAMP, 1 / 5.0f, { 0, 1, 2, 3 }, true);
	lamp4->GetSprite()->SetAnimation(CSimpleSprite::ANIM_LAMP);

	auto table11{ new Actor(MTable.name, App::CreateSprite(MTable.model3, 1, 1, MTable.frame, MTable.scale), new Vector2D(table2->GetPosition()->_x - 16, table2->GetPosition()->_y - 40), new Collision(32, 32)) };
	auto lamp5{ new Actor(MLamp.name, App::CreateSprite(MLamp.model, 4, 1, 0, MLamp.scale), new Vector2D(table11->GetPosition()->_x, table11->GetPosition()->_y + 16), new Collision(32, 32)) };
	lamp5->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_LAMP, 1 / 5.0f, { 0, 1, 2, 3 }, true);
	lamp5->GetSprite()->SetAnimation(CSimpleSprite::ANIM_LAMP);

	MirrorShard* shard2{ new MirrorShard(MMirrorShard.name + "2", App::CreateSprite(MPage.model , 1, 1), new Vector2D(shelf->GetPosition()->_x, shelf->GetPosition()->_y - 48 ), new Collision(32, 32)) };

	page->SetPosition(tp11->GetPosition()->_x, tp11->GetPosition()->_y - 64);

	/*NPC*/
	auto charlotte{ new NPC(MCharlotte.name, App::CreateSprite(MCharlotte.model, 3, 4, 7, MCharlotte.scale), new Vector2D(LIBRARY_WALL + 32, wallH2->GetPosition()->_y - 192), new Collision(32, 32)) };
	charlotte->dialogues.insert(std::make_pair(0, DCharlotte.l1));
	charlotte->dialogues.insert(std::make_pair(1, DCharlotte.l2));
	charlotte->SetCurrentDialogue(0);

	auto ralph{ new NPC("Ralph Neville", App::CreateSprite(MFamily.model, 3, 4, MFamily.frame, MFamily.scale), new Vector2D(MIDDLE_WIDTH + 80, wallH2->GetPosition()->_y - 64), new Collision(32, 32)) };
	ralph->dialogues.insert(std::make_pair(0, DFather.l1));
	ralph->SetCurrentDialogue(0);

	/*DIALOGUES*/
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };

	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(DDetective.l1);
	StateMain::SetState(State::DIALOGUE);

}

void Library::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Library::Render()
{
	Scene::Render();
}

void Library::Exit()
{
}

bool Library::IsRoomCleared()
{
	if (!_TPPuzzle)
		return false;

	if (!_TPPuzzle->IsCleared())
		return false;

	else if (_TPPuzzle->_status == Status::CLEARED)
		return true;

	else if (_TPPuzzle->_status == Status::PENDING)
	{
		auto it = std::find_if(_actors.begin(), _actors.end(), [](Actor* actor) { return actor->GetName() == "Ralph Neville"; });
		if (it != _actors.end())
		{
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

		stateDialogue->_currentDialogue.emplace_back(MMessage.door_unlocked);
		stateDialogue->_currentDialogue.emplace_back(DDetective.l2);

		StateMain::SetState(State::DIALOGUE);

		CSimpleSound::GetInstance().PlaySoundW(SFX.door_open, 0);

		/*Change the player's movement speed from now on*/
		StateMain::_player->SetMovementSpeed(5);
		_TPPuzzle->_status = Status::CLEARED;
		return true;
	}
}
