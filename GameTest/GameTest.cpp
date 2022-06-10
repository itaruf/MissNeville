//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <numeric>
#include <iterator>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <cmath>
#include <map>

#include "Player.h"
#include "Scene.h"
#include "Collision.h"
#include "Collectable.h"
#include "GameState.h"	
#include "Entrance.h"
#include "Inventory.h"
#include "StateRegular.h"
#include "StateInventory.h"
#include "StateDialogue.h"
#include "EState.h"
#include "Lounge.h"
#include "Room.h"
#include "Hall.h"
#include "Library.h"
#include "Utilities.h"

//#include "csv.h"

std::shared_ptr<GameState> gameState;

void Init()
{
	CSimpleSprite* dialBox{ App::CreateSprite(".\\TestData\\Icons\\hintbox2.bmp", 1, 1) };
	dialBox->SetPosition(APP_VIRTUAL_WIDTH / 2, 100);
	dialBox->SetScale(7);
	/*GameStates*/
	StateRegular* stateRegular = new StateRegular();
	StateInventory* stateInventory = new StateInventory();
	StateDialogue* stateDialogue = new StateDialogue(dialBox);

	/*Instantiate the gamestate which will be persistent across all scenes*/
	gameState = std::make_shared<GameState>();
	gameState->_state = State::REGULAR;

	/*Scenes*/
	Entrance* entrance = new Entrance{ 0, nullptr };
	Lounge* lounge = new Lounge{ 3 };
	Room* room = new Room{ 4 };
	Hall* hall = new Hall{ 1 };
	Library* library = new Library{ 2 };


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
	gameState->_currentScene = entrance;
	gameState->_currentScene->Init();

	/*Other scenes*/
	gameState->_gameStates.emplace_back(stateRegular);
	gameState->_gameStates.emplace_back(stateInventory);
	gameState->_gameStates.emplace_back(stateDialogue);
	gameState->_currentState = stateRegular;

	/*Instantiation du personnage*/
	CSimpleSprite* playerSprite{ App::CreateSprite(".\\TestData\\Characters\\Skeleton.bmp", 9, 4) };
	Vector2D* vector{ new Vector2D{ 300.0f, 200.0f } };
	Collision* collider{ new Collision(Collision::ColliderType::Block, 16, 16, new Vector2D(0, -10)) };
	Player* player{ new Player("Imane", playerSprite, vector, collider, 20, 4, new Inventory()) };

	/*Player base stats and configs*/
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7,8 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 9,10,11,12,13,14,15,16,17 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 18,19,20,21,22,23,24,25,26 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 27,28,29,30,31,32,33,34,35 });
	player->GetSprite()->SetScale(2.0f);

	/*Adding the player to the gamestate*/
	gameState->AddPlayer(player);
	stateRegular->_player = player;
	stateInventory->_player = player;
	stateDialogue->_player = player;

	// Test ambiance WIP (need to create a sound manager)
	/*App::PlaySoundW(".\\TestData\\SFX\\entrance.wav", true);*/
}

void Update(float deltaTime)
{ 

	if (gameState->_currentScene)
	{
		gameState->SwitchState();
		gameState->_currentScene->Update(deltaTime);
		gameState->_currentState->Update();
	}

	auto player{ gameState->GetPlayer() };

	if (player)
	{
		player->GetSprite()->Update(deltaTime);
	}
}

void Render()
{
	/*********CURRENT ROOM RENDER*********/
	if (!gameState->_currentScene)
		return;

	gameState->_currentScene->Render();
	App::Print(800, 620, ("Scene : " + GetChar(gameState->_currentScene->GetID())).c_str());
	App::Print(800, 600, ("State : " + gameState->PrintState()).c_str());
	gameState->_currentState->Render();

	/*********PLAYER RENDER*********/
	auto player{ gameState->GetPlayer() };

	if (!player)
		return;

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);

	/*SOME PRINTS*/
	if (gameState->_currentScene->IsRoomCleared())
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