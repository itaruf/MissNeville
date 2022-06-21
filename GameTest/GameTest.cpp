//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "../stdafx.h"
//------------------------------------------------------------------------
//#include "StateMain.h"	
#include "Player.h"

#include "StateRegular.h"
#include "StateInventory.h"
#include "StateDialogue.h"

#include "EState.h"
#include "Hall.h"
#include "Lounge.h"
#include "Room.h"
#include "Hall.h"
#include "Library.h"
#include "Utilities.h"
#include "Controller.h"
#include "PlayerController.h"

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

	/*Scenes*/
	Entrance* entrance{ new Entrance{ 0 } };
	Lounge* lounge{ new Lounge{ 3 } };
	Room* room{ new Room{ 4 } };
	Hall* hall{ new Hall{ 1, nullptr} };
	Library* library{ new Library{ 2 } };


	/*Linking scenes*/
	entrance->_NScene = hall;
	lounge->_EScene = hall;
	room->_SScene = hall;
	library->_WScene = hall;

	hall->_NScene = room;
	hall->_WScene = lounge;
	hall->_SScene = entrance;
	hall->_EScene = library;

	/*Setting up the first scene*/
	/*state->_currentScene = entrance;*/
	state->_currentScene = hall;
	/*state->_currentScene = lounge;*/
	/*state->_currentScene = library;*/
	/*state->_currentScene = room;*/
	
	state->_rooms.insert(std::make_pair(0, entrance));
	state->_rooms.insert(std::make_pair(1, hall));
	state->_rooms.insert(std::make_pair(2, room));
	state->_rooms.insert(std::make_pair(3, library));
	state->_rooms.insert(std::make_pair(4, lounge));

	/*Instantiation du personnage*/
	CSimpleSprite* playerSprite{ App::CreateSprite(".\\TestData\\Characters\\Skeleton.bmp", 9, 4) };
	Vector2D* vector{ new Vector2D{ MIDDLE_WIDTH, 350.0f } };
	Collision* collider{ new Collision(24, 24, Collision::ColliderType::Block, new Vector2D(0, -10))};
	PlayerController* controller{ new PlayerController() };
	Player* player{ new Player("JJ Detective", playerSprite, vector, collider, 20, 4, controller, new Inventory())};
	player->SetTag("player");
	player->_interactSprite = App::CreateSprite(MIcon.model, 1, 1, MIcon.frame, MIcon.scale);
	/*Player base stats and configs*/
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7,8 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 9,10,11,12,13,14,15,16,17 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 18,19,20,21,22,23,24,25,26 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 27,28,29,30,31,32,33,34,35 });
	player->GetSprite()->SetScale(2.0f);

	player->dialogues.insert(std::make_pair(0, "["+ player->GetName() + "] says : The mirror shattered in pieces !"));
	player->dialogues.insert(std::make_pair(1, "[" + player->GetName() + "] says : I need to find all the missing pieces... But why would they spread everywhere in the mansion ?"));
	//player->dialogues.insert(std::make_pair(2, "[" + player->GetName() + "] says : The mirror shattered in pieces !"));
	player->SetCurrentDialogue(0);

	/*Adding the player to the gamestate*/
	state->AddPlayer(player);
	stateRegular->_player = player;
	stateInventory->_player = player;
	stateDialogue->_player = player;

	entrance->AddActor(player);
	hall->AddActor(player);
	room->AddActor(player);
	library->AddActor(player);
	lounge->AddActor(player);

	/*Other states*/
	state->_stateControllers.emplace_back(stateRegular);
	state->_stateControllers.emplace_back(stateInventory);
	state->_stateControllers.emplace_back(stateDialogue);
	state->_currentStateController = stateRegular;

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

	/*********PLAYER RENDER*********/
	auto player{ state->GetPlayer() };

	if (!player)
		return;

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);

	/*SOME PRINTS*/
	if (state->_currentScene->IsRoomCleared())
		App::Print(800, 700, "Scene Cleared");
	else
		App::Print(800, 700, "Scene Not Cleared");
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.²
//------------------------------------------------------------------------
void Shutdown()
{
}