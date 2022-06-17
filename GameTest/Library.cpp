#include "../stdafx.h"
#include "Library.h"

Library::Library(int ID, std::vector<Actor*> actors) : Scene(ID, actors)
{
}

Library::Library(int ID) : Scene(ID)
{
}

Library::~Library()
{
}

bool Library::Init()
{
	if (Scene::Init())
		return true;

	startingPos = new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2 - 128);
	
	StateMain::_player->SetPosition(startingPos);

	TriggerScene* hallTrigger{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(WALL_OFFSET + TRIGGER_OFFSET, APP_VIRTUAL_HEIGHT / 2), new Collision(32, 32, Collision::ColliderType::Overlap), _WScene, new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET, APP_VIRTUAL_HEIGHT / 2)) };
	
	auto wallH2{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, (MIDDLE_HEIGHT + 64)), new Collision(2, MIDDLE_WIDTH + WALL_OFFSET * 2)) };
	wallH2->SetTag("wall");
	
	auto wallV2{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH - 128, wallH2->GetPosition()->_y / 2 + 64), new Collision(MIDDLE_HEIGHT / 2 + WALL_OFFSET, 2)) };
	wallV2->SetTag("wall");
	
	auto wallV3{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(wallV2->GetPosition()->_x + 256, wallH2->GetPosition()->_y / 2 + 64), new Collision(MIDDLE_HEIGHT / 2 + WALL_OFFSET, 2)) };
	wallV2->SetTag("wall");
	
	auto wallV4{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(MIDDLE_WIDTH, wallH2->GetPosition()->_y + 100), new Collision(MIDDLE_HEIGHT - WALL_OFFSET * 2 + 64, 2)) };
	wallV2->SetTag("wall");
	
	/* Triggers*/
	
	// First Part
	TriggerScene* tp1{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 100), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos)};
	
	TriggerScene* tp2{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y - 200), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, new Vector2D(wallV4->GetPosition()->_x + 128,  wallH2->GetPosition()->_y + 128)) };
	
	// Second Part
	TriggerScene* tp3{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV4->GetPosition()->_x + 256,  wallH2->GetPosition()->_y + 128), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET - TRIGGER_OFFSET - NEW_PLAYER_POS_OFFSET, APP_VIRTUAL_HEIGHT / 2)) };
	
	TriggerScene* tp4{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV4->GetPosition()->_x + 256,  wallH2->GetPosition()->_y + 64), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos) };
	
	TriggerScene* tp5{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV4->GetPosition()->_x + 128,  wallH2->GetPosition()->_y + 64), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos) };
	
	// Third Part
	TriggerScene* tp6{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV3->GetPosition()->_x + 128,  wallH2->GetPosition()->_y - 100), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos) };
	
	TriggerScene* tp7{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV3->GetPosition()->_x + 128,  wallH2->GetPosition()->_y - 200), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y + 64)) };
	
	// Fourth Part
	TriggerScene* tp8{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x - 100, wallH2->GetPosition()->_y + 128), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos) };
	
	TriggerScene* tp9{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x , wallH2->GetPosition()->_y + 128), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, new Vector2D(APP_VIRTUAL_WIDTH / 2 , APP_VIRTUAL_HEIGHT / 2 - 64)) };
	
	TriggerScene* tp10{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(wallV2->GetPosition()->_x , wallH2->GetPosition()->_y + 64), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos) };
	
	// Fifth Part 
	TriggerScene* tp11{ new TriggerScene(MTriggerScene.name, App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale), new Vector2D(APP_VIRTUAL_WIDTH / 2 , APP_VIRTUAL_HEIGHT / 2 - 128), new Collision(32, 32, Collision::ColliderType::Overlap), nullptr, startingPos)};
	
	/*Props*/
	auto shelf{ new Actor(MShelf.name, App::CreateSprite(MShelf.model, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(WALL_OFFSET + 16, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	auto shelf2{ new Actor(MShelf.name, App::CreateSprite(MShelf.model, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	auto shelf3{ new Actor(MShelf.name, App::CreateSprite(MShelf.model2, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf2->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	auto shelf4{ new Actor(MShelf.name, App::CreateSprite(MShelf.model, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf3->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	auto shelf5{ new Actor(MShelf.name, App::CreateSprite(MShelf.model3, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf4->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	auto shelf6{ new Actor(MShelf.name, App::CreateSprite(MShelf.model5, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf5->GetPosition()->_x + 48, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	auto shelf7{ new Actor(MShelf.name, App::CreateSprite(MShelf.model5, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf6->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };
	
	/*First Part*/
	auto commode{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH - 128, wallH2->GetPosition()->_y - 64), new Collision(64, 32)) };
	
	auto commode2{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH - 128, commode->GetPosition()->_y - 92), new Collision(64, 32)) };
	
	auto commode3{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH - 128, commode2->GetPosition()->_y - 92), new Collision(64, 32)) };
	
	auto shelf8{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(WALL_OFFSET + 24, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	auto shelf9{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf8->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	auto shelf10{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf9->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	auto shelf11{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf10->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	auto shelf12{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf11->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	auto shelf13{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf12->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	auto shelf14{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf13->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };
	
	/*Second Part*/
	auto commode7{ new Actor(MShelf.name, App::CreateSprite(MCommode.model6, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH, wallH2->GetPosition()->_y + 46), new Collision(64, 32)) };

	auto commode8{ new Actor(MShelf.name, App::CreateSprite(MCommode.model7, 1, 1, MCommode.frame, MCommode.scale), new Vector2D(MIDDLE_WIDTH, commode7->GetPosition()->_y + 92), new Collision(64, 32)) };

	auto shelf28{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(wallV4->GetPosition()->_x + 96, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf29{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf28->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf30{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf29->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf31{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf30->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf32{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf31->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf33{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf32->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf34{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf33->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf35{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf34->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	auto shelf36{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf35->GetPosition()->_x + 32, APP_VIRTUAL_HEIGHT - WALL_OFFSET - TRIGGER_OFFSET), new Collision(64, 32)) };

	/*Third Part*/
	auto shelf21{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(wallV3->GetPosition()->_x + 40, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto shelf22{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf21->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto shelf23{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf22->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto shelf24{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf23->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto shelf25{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf24->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto shelf26{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf25->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

	auto shelf27{ new Actor(MShelf.name, App::CreateSprite(MShelf.model6, 1, 1, MShelf.frame, MShelf.scale), new Vector2D(shelf26->GetPosition()->_x + 32, wallH2->GetPosition()->_y - 16), new Collision(64, 32)) };

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
	
	return false;
}

void Library::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Library::Render()
{
	Scene::Render();
}

bool Library::IsRoomCleared()
{
	return false;
}
