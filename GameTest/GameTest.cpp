//------------------------------------------------------------------------
// GameIntro.cpp
//------------------------------------------------------------------------
#include "../stdafx.h"
//------------------------------------------------------------------------
//#include "StateMain.h"	
#include "Player.h"

#include "StateRegular.h"
#include "StateInventory.h"
#include "StateDialogue.h"

#include "EState.h"

#include "Intro.h"
#include "Hall.h"
#include "Kitchen.h"
#include "Room.h"
#include "Hall.h"
#include "Library.h"
#include "Outro.h"

#include "Utilities.h"
#include "Controller.h"
#include "PlayerController.h"
#include <typeinfo>

std::shared_ptr<StateMain> state;

void Init()
{
	CSimpleSprite* dialBox{ App::CreateSprite(".\\TestData\\Icons\\hintbox2.bmp", 1, 1) };
	dialBox->SetPosition(MIDDLE_WIDTH, 100);
	dialBox->SetScale(7);

	/*GameStates*/
	StateRegular* stateRegular{ new StateRegular() };
	StateInventory* stateInventory{ new StateInventory() };
	StateDialogue* stateDialogue{ new StateDialogue(dialBox) };

	/*Instantiate the gamestate which will be persistent across all scenes*/
	state = std::make_shared<StateMain>();
	state->_state = State::REGULAR;

	/*Instantiation du personnage*/
	CSimpleSprite* playerSprite{ App::CreateSprite(".\\TestData\\Characters\\player.bmp", 3, 4) };
	Vector2D* vector{ new Vector2D{ MIDDLE_WIDTH, 350.0f } };
	Collision* collider{ new Collision(24, 24, ColliderType::Block, new Vector2D(0, -10)) };
	PlayerController* controller{ new PlayerController() };
	Player* player{ new Player("JJ Detective", playerSprite, vector, collider, 20, 4, controller, new Inventory()) };
	player->SetTag("player");
	player->_interactSprite = App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale);
	/*Player base stats and configs*/
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 9, 10, 11 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 3, 4, 5 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 0, 1, 2 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 6, 7, 8 });
	player->GetSprite()->SetScale(3.0f);

	/*Adding the player to the gamestate*/
	state->SetPlayer(player);
	stateRegular->_player = player;
	stateInventory->_player = player;
	stateDialogue->_player = player;

	/*Other states*/
	state->_stateControllers.emplace_back(stateRegular);
	state->_stateControllers.emplace_back(stateInventory);
	state->_stateControllers.emplace_back(stateDialogue);
	state->_currentStateController = stateRegular;

	/*Scenes*/
	Intro* intro{ new Intro { 0 } };
	Hall* hall{ new Hall{ 1, new CandlePuzzle()} };
	Room* room{ new Room{ 2, new MirrorPuzzle()} };
	Library* library{ new Library{ 3, new TPPuzzle() } };
	Kitchen* kitchen{ new Kitchen{ 4, new DodgePuzzle() } };
	Entrance* entrance{ new Entrance{ 5 } };
	Outro* outro{ new Outro{ 6 } };

	/*entrance->AddActor(player);
	hall->AddActor(player);
	room->AddActor(player);
	library->AddActor(player);*/

	/*Linking scenes*/
	entrance->_NScene = hall;
	kitchen->_EScene = hall;
	room->_SScene = hall;
	library->_WScene = hall;

	hall->_NScene = room;
	hall->_WScene = kitchen;
	hall->_SScene = entrance;
	hall->_EScene = library;

	/*Setting up the first scene*/
	/*state->_currentScene = entrance;*/
	/*state->_currentScene = hall;*/
	/*state->_currentScene = kitchen;*/
	/*state->_currentScene = library;*/
	/*state->_currentScene = room;*/
	state->_currentScene = intro;
	
	state->_rooms.insert(std::make_pair(0, intro));
	state->_rooms.insert(std::make_pair(1, hall));
	state->_rooms.insert(std::make_pair(2, room));
	state->_rooms.insert(std::make_pair(3, library));
	state->_rooms.insert(std::make_pair(4, kitchen));
	state->_rooms.insert(std::make_pair(5, entrance));
	state->_rooms.insert(std::make_pair(6, outro));

	state->_currentScene->Init();
	CSimpleSound::GetInstance().PlaySound(SFX.scene, true, -3500);
}

void Update(float deltaTime)
{ 
	if (state->_currentScene)
	{
		state->SwitchState();
		state->_currentScene->Update(deltaTime);
		state->_currentStateController->Update();
	}
}

void Render()
{
	/*********CURRENT ROOM RENDER*********/
	if (!state->_currentScene)
		return;

	state->_currentScene->Render();
	App::Print(800, 620, ("Scene : " + GetChar(state->_currentScene->GetID())).c_str());
	App::Print(800, 600, ("State : " + state->PrintState()).c_str());
	state->_currentStateController->Render();

	state->_currentStateController->Render();

	/*SOME PRINTS*/
	
	if (!state->_currentScene->initialized)
		return;

	if (state->_currentScene->IsRoomCleared())
		App::Print(800, 700, "Scene Cleared");
	else
		App::Print(800, 700, "Scene Not Cleared");

	/*********PLAYER RENDER*********/
	auto player{ state->GetPlayer() };

	if (!player)
		return;

	if (!player->GetSprite())
		return;

	if (state->_rooms[2]->initialized && !state->_rooms[2]->IsRoomCleared())
	{
		int nb{ 0 };
		for (const auto& item : player->_inventory->_bags[0].second)
		{
			auto mshard{ dynamic_cast<MirrorShard*>(item) };
			if (mshard)
				nb++;
		}

		auto it = std::find_if(StateMain::_rooms[2]->GetActors().begin(), StateMain::_rooms[2]->GetActors().end(), [](Actor* actor) { return actor->GetTag() == "Mirror"; });

		if (it != StateMain::_rooms[2]->GetActors().end())
			App::Print(800, 580, ("Number of shards : " + GetChar(nb) + " / " + GetChar(dynamic_cast<Mirror*>(*it)->GetNbShards())).c_str());
	}
		
	
	if (player->_footStep)
	{
		player->_footStep->Draw();
		player->_footStep->SetPosition(player->GetPosition()->_x, player->GetPosition()->_y - 20);
	}

	if (state->_currentScene == state->_rooms[0] || state->_currentScene == state->_rooms[6])
		return;

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.²
//------------------------------------------------------------------------
void Shutdown()
{
}