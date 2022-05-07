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
	gameState = std::make_unique<GameState>();
	gameState->currentRoom  = new Room(0);

	/*Instantiation du personnage*/
	CSimpleSprite* testSprite = App::CreateSprite(".\\TestData\\Skeleton.bmp", 9, 4);
	Vector2D vector{ 400.0f, 100.0f };
	Collision* collider = new Collision(Collision::ColliderType::Block, 25, 15);
	Character* player = new Character("Imane", testSprite, vector, collider, gameState->currentRoom, 20, 5);

	CSimpleSprite* bloodSprite = App::CreateSprite(".\\TestData\\broken-glasses-blood.bmp", 5, 4);
	Collision* bloodCollision = new Collision(Collision::ColliderType::Block, 15, 15);

	Vector2D bloodPos{ 385,400 };
	Item* blood = new Item("Blood", bloodSprite, bloodPos, bloodCollision, gameState->currentRoom);

	blood->GetSprite()->SetFrame(0);
	blood->GetSprite()->SetScale(2);

	Collision* candleCollision = new Collision(Collision::ColliderType::Block, 20, 15);
	CSimpleSprite* candleSprite = App::CreateSprite(".\\TestData\\candle.bmp", 1, 2);
	Vector2D candlePos{400,300 };
	Item* candle = new Item("Candle", candleSprite, candlePos, candleCollision, gameState->currentRoom);
	candle->GetSprite()->SetFrame(1);
	candle->GetSprite()->SetScale(0.5);

	gameState->currentRoom->AddPlayer(player);

	/*Caractéristiques de bases*/
	gameState->currentRoom->GetPlayer()->SetName("test");
	gameState->currentRoom->GetPlayer()->SetHP(50);
	gameState->currentRoom->GetPlayer()->GetSprite()->CreateAnimation(gameState->currentRoom->GetPlayer()->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7,8 });
	gameState->currentRoom->GetPlayer()->GetSprite()->CreateAnimation(gameState->currentRoom->GetPlayer()->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 9,10,11,12,13,14,15,16,17 });
	gameState->currentRoom->GetPlayer()->GetSprite()->CreateAnimation(gameState->currentRoom->GetPlayer()->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 18,19,20,21,22,23,24,25,26 });
	gameState->currentRoom->GetPlayer()->GetSprite()->CreateAnimation(gameState->currentRoom->GetPlayer()->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 27,28,29,30,31,32,33,34,35 });
	gameState->currentRoom->GetPlayer()->GetSprite()->SetScale(2.0f);

	CSimpleSprite* testSprite2 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite2->SetFrame(2);
	testSprite2->SetScale(0.5f);

	CSimpleSprite* testSprite3 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite3->SetFrame(2);
	testSprite3->SetScale(0.5f);

	Vector2D vector2{ 400.0f, 400.0f };
	Collision* collider2 = new Collision(Collision::ColliderType::Block, 15, 15);

	Actor* item = new Actor("Item1", testSprite2, vector2, collider2, gameState->currentRoom);

	Vector2D vector3{ 400.f, 200.f };
	Collision* collider3 = new Collision(Collision::ColliderType::Overlap, 40, 40);

	Actor* item2 = new Actor("Item2", testSprite3, vector3, collider3, gameState->currentRoom);

	gameState->currentRoom->AddActor(player);
	gameState->currentRoom->AddActor(item);
	gameState->currentRoom->AddActor(item2);
	gameState->currentRoom->AddActor(blood);
	gameState->currentRoom->AddActor(candle);
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
	for each (const auto & item in gameState->currentRoom->GetActors())
	{
		item->GetSprite()->Update(deltaTime);
	}

	if (gameState->currentRoom->GetPlayer() != nullptr)
	{
		gameState->currentRoom->GetPlayer()->isMoving();
		gameState->currentRoom->GetPlayer()->MoveHorizontally();
		gameState->currentRoom->GetPlayer()->MoveVertically();
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------

std::string returnInt(int x) 
{
	return std::to_string(x);
}
void Render()
{
	/*std::string(*ptr)(int);
	ptr = &returnInt;

	App::Print(700, 500, (*ptr)(5).c_str());*/

	App::Print(700, 500, GetChar(gameState->currentRoom->GetPlayer()->GetPosition().x).c_str());

	for each (const auto & item in gameState->currentRoom->GetActors())
	{
		item->GetSprite()->Draw();
		item->GetCollider()->DrawCollision(item, 50, 50, 50);
	}

	auto pos = gameState->currentRoom->GetPlayer()->GetPosition();
	auto string = std::to_string(pos.x) + " " + std::to_string(pos.y);

	App::Print(100, 20, ("Player Pos: " + string).c_str());
	App::Print(800, 650, ("Player H (Spr): " + std::to_string(gameState->currentRoom->GetPlayer()->GetSprite()->GetHeight())).c_str());
	App::Print(800, 675, ("Player W (Spr): " + std::to_string(gameState->currentRoom->GetPlayer()->GetSprite()->GetWidth())).c_str());
	App::Print(800, 625, ("Player H (Col): " + std::to_string(gameState->currentRoom->GetPlayer()->GetCollider()->GetHeight())).c_str());
	App::Print(800, 600, ("Player W (Col): " + std::to_string(gameState->currentRoom->GetPlayer()->GetCollider()->GetWidth())).c_str());
	App::Print(800, 575, ("Player Name: " + gameState->currentRoom->GetPlayer()->GetName()).c_str());
	App::Print(900, 500, std::to_string(App::GetController().GetLeftThumbStickY()).c_str());
	App::Print(900, 450, std::to_string(App::GetController().GetLeftThumbStickX()).c_str());

	float UpRange = 50;
	auto player = gameState->currentRoom->GetPlayer();

	if (player->GetDirection() == Direction::UP)
	{
		std::vector<int> rangeUp{};
		for (int i = 1; i < gameState->currentRoom->GetActors().size(); i++)
		{
			auto item = gameState->currentRoom->GetActors()[i];
			if (player->GetCollider()->isColliding(player, item, player->GetPosition().x, player->GetPosition().y + player->GetMovementSpeed()))
			{
				if (item->GetPosition().x == player->GetPosition().x)
				{
					auto ecartPlayer = static_cast<int>(std::abs((player->GetPosition().y + player->GetCollider()->height) - (player->GetPosition().y + player->GetCollider()->height + UpRange)));

					try 
					{
						rangeUp.clear();
						rangeUp.resize(ecartPlayer + 1);
						std::iota(std::begin(rangeUp), std::end(rangeUp), player->GetPosition().y + player->GetCollider()->height); // generate numbers from begin to end
					}
					catch (const std::length_error& le)
					{
						App::Print(350, 450, le.what());
					}

					auto ecartItem = static_cast<int>(std::abs((item->GetCollider()->GetDownLeftColPos(item))->y) - (item->GetCollider()->GetUpLeftColPos(item)->y));

					auto it = std::find(rangeUp.begin(), rangeUp.end(), gameState->currentRoom->GetActor(i)->GetPosition().y);

					if (it != rangeUp.end()) 
					{
						App::Print(0 + i * 50, 650, gameState->currentRoom->GetActor(i)->GetName().c_str());
					}
					else 
					{
						App::Print(650, 650, "NOT ITEM IN RANGE (FORWARD)");
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}