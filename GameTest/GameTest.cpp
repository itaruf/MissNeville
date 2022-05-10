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
#include "Character.h"
#include "Room.h"
#include "Collision.h"
#include "Item.h"
#include "GameState.h"	
#include "Entrance.h"

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
#include <stdexcept> // std::length_error

std::unique_ptr<GameState> gameState;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	/*Instantiation du personnage*/
	CSimpleSprite* playerSprite = App::CreateSprite(".\\TestData\\Skeleton.bmp", 9, 4);
	Vector2D* vector = new Vector2D{ 300.0f, 200.0f };
	Collision* collider = new Collision(Collision::ColliderType::Block, 16, 16);
	Character* player = new Character("Imane", playerSprite, vector, collider, nullptr, 20, 4);

	/*Caractéristiques de bases*/
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7,8 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 9,10,11,12,13,14,15,16,17 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 18,19,20,21,22,23,24,25,26 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 27,28,29,30,31,32,33,34,35 });
	player->GetSprite()->SetScale(2.0f);

	gameState = std::make_unique<GameState>();
	gameState->AddPlayer(player);
	gameState->entrance = new Entrance{ 0, nullptr }; 
	gameState->currentRoom = gameState->entrance;
	/*gameState->currentRoom->AddActor(player);*/
	player->SetCurrentRoom(gameState->currentRoom);
	gameState->entrance->gameState = gameState.get();
	gameState->entrance->Init();
}

template<
	typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
std::string GetChar(const T& var)
{
	return std::to_string(var);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	auto player = gameState->GetPlayer();
	gameState->entrance->Update(deltaTime);

	for each (const auto & item in gameState->currentRoom->GetActors())
	{
		item->GetSprite()->Update(deltaTime);
	}

	if (player != nullptr)
	{
		player->GetSprite()->Update(deltaTime);
		player->isMoving();
		player->MoveHorizontally();
		player->MoveVertically();
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------


void Render()
{
	auto player = gameState->GetPlayer();

	/*std::string(*ptr)(int);
	ptr = &returnInt;

	App::Print(700, 500, (*ptr)(5).c_str());*/

	App::Print(500, 450, std::to_string(gameState->entrance->GetActors().size()).c_str());

	gameState->entrance->Render();

	for each (const auto & item in gameState->currentRoom->GetActors())
	{
		item->GetSprite()->Draw();
		item->GetCollider()->DrawCollision(item, 50, 50, 50);
	}

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);

	auto pos = player->GetPosition();
	auto string = std::to_string(pos->x) + " " + std::to_string(pos->y);

	App::Print(100, 20, ("Player Pos: " + string).c_str());
	App::Print(800, 650, ("Player H (Spr): " + std::to_string(player->GetSprite()->GetHeight())).c_str());
	App::Print(800, 675, ("Player W (Spr): " + std::to_string(player->GetSprite()->GetWidth())).c_str());
	App::Print(800, 625, ("Player H (Col): " + std::to_string(player->GetCollider()->GetHeight())).c_str());
	App::Print(800, 600, ("Player W (Col): " + std::to_string(player->GetCollider()->GetWidth())).c_str());
	App::Print(800, 575, ("Player Name: " + player->GetName()).c_str());
	App::Print(900, 500, std::to_string(App::GetController().GetLeftThumbStickY()).c_str());
	App::Print(900, 450, std::to_string(App::GetController().GetLeftThumbStickX()).c_str());

	// Horizontally
	if (player->GetDirection() == Direction::RIGHT || player->GetDirection() == Direction::LEFT)
	{
		float ms = player->GetMovementSpeed();
		if (player->GetDirection() == Direction::LEFT)
			ms = -player->GetMovementSpeed();
		auto actors = gameState->currentRoom->GetActors();
		try
		{
			if (actors.size() != 0)
			{
				std::sort(std::begin(actors), std::end(actors), [player](Actor* const& l, Actor* const& r)
					{
						return 
							std::sqrt(std::pow(player->GetPosition()->x - l->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - l->GetPosition()->y, 2))
							< 
							std::sqrt(std::pow(player->GetPosition()->x - r->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - r->GetPosition()->y, 2));
					});
				if (static_cast<Item*>(actors[0])->GetInteractivity() == Interactivity::Interactive)
				{
					App::Print(100, 600, ("Closest Item to Player : " + actors[0]->GetName()).c_str());
					if (player->GetCollider()->isColliding(player, actors[0], player->GetPosition()->x + ms, player->GetPosition()->y))
					{
						if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
							player->UseLighter(static_cast<Candle*>(actors[0]));
					}
				}
			}
		}
		catch (const std::length_error& le)
		{
			App::Print(350, 450, le.what());
		}
	}

	// Vertically
	if (player->GetDirection() == Direction::UP || player->GetDirection() == Direction::DOWN)
	{
		float ms = player->GetMovementSpeed();
		if (player->GetDirection() == Direction::DOWN)
			ms = -player->GetMovementSpeed();
		auto actors = gameState->currentRoom->GetActors();
		try
		{
			if (actors.size() != 0)
			{
				std::sort(std::begin(actors), std::end(actors), [player](Actor* const& l, Actor* const& r)
					{
						return
							std::sqrt(std::pow(player->GetPosition()->x - l->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - l->GetPosition()->y, 2))
							<
							std::sqrt(std::pow(player->GetPosition()->x - r->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - r->GetPosition()->y, 2));
					});

				if (static_cast<Item*>(actors[0])->GetInteractivity() == Interactivity::Interactive)
				{
					App::Print(100, 600, ("Closest Item to Player : " + actors[0]->GetName()).c_str());
					if (player->GetCollider()->isColliding(player, actors[0], player->GetPosition()->x, player->GetPosition()->y + ms))
					{
						if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
							player->UseLighter(static_cast<Candle*>(actors[0]));
					}
				}
			}
		}
		catch (const std::length_error& le)
		{
			App::Print(350, 450, le.what());
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