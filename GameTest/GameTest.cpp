//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
//#include "app\app.h"
//------------------------------------------------------------------------
#include "Player.h"
#include "Scene.h"
#include "Collision.h"
#include "Collectable.h"

class GameState;
#include "GameState.h"	

#include "Entrance.h"
#include "Inventory.h"
//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------

#include <numeric>
#include <iterator>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <cmath>
#include <map>

//class GameStateController;
//#include "GameStateController.h"

class StateRegular;
#include "StateRegular.h"

class StateInventory;
#include "StateInventory.h"

class StateDialogue;
#include "StateDialogue.h"

//#include "csv.h"

enum class State;
#include "EState.h"

std::shared_ptr<GameState> gameState;

void Init()
{
	/*GameStates*/
	StateRegular* stateRegular = new StateRegular();
	StateInventory* stateInventory = new StateInventory();
	StateDialogue* stateDialogue = new StateDialogue();

	/*Instantiate the gamestate which will be persistent across all scenes*/
	gameState = std::make_shared<GameState>();

	gameState->state = State::REGULAR;
	/*Setting up the first scene*/
	gameState->currentScene = new Entrance(0, nullptr);
	gameState->currentScene->Init();

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

	stateRegular->player = player;

	// Test ambiance WIP (need to create a sound manager)
	/*App::PlaySoundW(".\\TestData\\SFX\\entrance.wav", true);*/

	gameState->gameStates.emplace_back(dynamic_cast<GameStateController*>(stateRegular));
	gameState->gameStates.emplace_back(dynamic_cast<GameStateController*>(stateInventory));
	gameState->gameStates.emplace_back(dynamic_cast<GameStateController*>(stateDialogue));
	gameState->currentState = stateRegular;
}

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
std::string GetChar(const T& var)
{
	return std::to_string(var);
}

void Update(float deltaTime)
{ 
	if (gameState->player)
		gameState->currentState->Update();

	if (gameState->currentScene)
	{
		gameState->SwitchState();
		gameState->currentScene->Update(deltaTime);
	}

	auto player{ gameState->GetPlayer() };

	if (player)
	{
		player->GetSprite()->Update(deltaTime);
	}
}

void Render()
{
	/*std::string(*ptr)(int);
	ptr = &returnInt;

	App::Print(700, 500, (*ptr)(5).c_str());*/
	
	/*********CURRENT ROOM RENDER*********/
	if (!gameState->currentScene)
		return;

	gameState->currentScene->Render();
	App::Print(800, 600, ("State : " + gameState->PrintState()).c_str());

	/*********PLAYER RENDER*********/
	auto player{ gameState->GetPlayer() };

	if (!player)
		return;

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);

	auto pos{ player->GetPosition() };
	auto string{ std::to_string(pos->x) + " " + std::to_string(pos->y) };

	/*SOME PRINTS*/
	if (gameState->currentScene->IsRoomCleared())
		App::Print(800, 700, "Scene Cleared");
	else
		App::Print(800, 700, "Scene Not Cleared");

	/*App::Print(200, 400, ("Nb of actors : " + GetChar(gameState->currentScene->GetActors().size())).c_str());
	App::Print(200, 300, ("Page collected : " + GetChar(player->inventory->bags[0].second.size())).c_str());
	App::Print(100, 20, ("Player Pos: " + string).c_str());
	App::Print(800, 650, ("Player H (Spr): " + std::to_string(player->GetSprite()->GetHeight())).c_str());
	App::Print(800, 675, ("Player W (Spr): " + std::to_string(player->GetSprite()->GetWidth())).c_str());
	App::Print(800, 625, ("Player H (Col): " + std::to_string(player->GetCollider()->GetHeight())).c_str());
	App::Print(800, 600, ("Player W (Col): " + std::to_string(player->GetCollider()->GetWidth())).c_str());
	App::Print(800, 575, ("Player Name: " + player->GetName()).c_str());
	App::Print(900, 500, std::to_string(App::GetController().GetLeftThumbStickY()).c_str());
	App::Print(900, 450, std::to_string(App::GetController().GetLeftThumbStickX()).c_str());*/

	/*********PLAYER'S INTERACTIONS*********/
	/*TEST WIP*/
	auto actors{ gameState->currentScene->GetActors() };
	if (actors.size() != 0)
	{
		std::vector<Actor*> interactiveActors{};
		// Select all Collectable or Interactive actors
		for (auto& actor : actors)
			if (dynamic_cast<ICollectable*>(actor) || dynamic_cast<IInteractive*>(actor))
				interactiveActors.emplace_back(actor);

		float ms{ player->GetMovementSpeed() };

		if (player->GetDirection() == Direction::LEFT || player->GetDirection() == Direction::DOWN)
			ms = -player->GetMovementSpeed();

		float x{ 0 };
		float y{ 0 };

		if (player->GetDirection() == Direction::RIGHT || player->GetDirection() == Direction::LEFT)
		{
			x = pos->x + ms;
			y = pos->y;
		}
		else
		{
			x = pos->x;
			y = pos->y + ms;
		}

		if (interactiveActors.size() > 0) 
		{
			/*SORT : FROM CLOSEST ACTOR TO FARTHEST*/
			std::sort(std::begin(interactiveActors), std::end(interactiveActors), [pos, ms](Actor* const& l, Actor* const& r)
				{
					return
						std::abs(pos->x + ms - l->GetPosition()->x + ms) + std::abs(pos->y + ms - l->GetPosition()->y + ms)
						<
						std::abs(pos->x + ms - r->GetPosition()->x + ms) + std::abs(pos->y + ms - r->GetPosition()->y + ms);
				});


			
			auto closestActor = interactiveActors[0];

			App::Print(100, 600, ("Closest Item to Player : " + closestActor->GetName()).c_str());

			/*PLAYER CAN INTERACT WITH ITEMS ONLY IF HE COLLIDES WITH THEM*/
			if (player->GetCollider()->isColliding(player, closestActor, x, y))
			{
			
				/*INTERACT WITH NON COLLECTIBLE ITEMS*/
				auto interactable = dynamic_cast<IInteractive*>(closestActor);
				if (interactable)
				{
					player->Interact(interactable);
					return;
				}
				/*COLLECT ITEMS*/
				auto collectable = dynamic_cast<Collectable*>(closestActor);
				if (collectable)
				{
					player->Interact(collectable);
					return;
				}
			}
		}
	}
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.²
//------------------------------------------------------------------------
void Shutdown()
{
}