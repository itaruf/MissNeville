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
#include <stdexcept> // std::length_error

std::shared_ptr<GameState> gameState;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	gameState = std::make_shared<GameState>();
	gameState->currentRoom = std::make_shared<Entrance>(0, gameState, nullptr);

	/*Instantiation du personnage*/
	CSimpleSprite* playerSprite{ App::CreateSprite(".\\TestData\\Skeleton.bmp", 9, 4) };
	Vector2D* vector{ new Vector2D{ 300.0f, 200.0f } };
	Collision* collider{ new Collision(Collision::ColliderType::Block, 16, 16, new Vector2D(0, -10)) };
	Inventory* inventory{ new Inventory() };
	Character* player{ new Character("Imane", playerSprite, vector, collider, gameState->currentRoom, 20, 4, inventory) };

	/*Caractéristiques de bases*/
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7,8 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 9,10,11,12,13,14,15,16,17 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 18,19,20,21,22,23,24,25,26 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 27,28,29,30,31,32,33,34,35 });
	player->GetSprite()->SetScale(2.0f);

	gameState->AddPlayer(player);

	/*gameState->currentRoom->AddActor(player);*/
	player->SetCurrentRoom(gameState->currentRoom);
	gameState->currentRoom->Init();

	playerSprite = nullptr;
	vector = nullptr;
	collider = nullptr;
	inventory = nullptr;
	player = nullptr;

	delete playerSprite;
	delete vector;
	delete collider;
	delete inventory;
	delete player;
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
	auto player{ gameState->GetPlayer() };

	if (player)
	{
		player->GetSprite()->Update(deltaTime);
		player->isMoving();
		player->MoveHorizontally();
		player->MoveVertically();
	}

	if (gameState->currentRoom)
		gameState->currentRoom->Update(deltaTime);

	player = nullptr;
	delete player;
}

void Render()
{
	/*std::string(*ptr)(int);
	ptr = &returnInt;

	App::Print(700, 500, (*ptr)(5).c_str());*/
	
	/*CURRENT ROOM RENDER*/
	if (!gameState->currentRoom)
		return;

	gameState->currentRoom->Render();

	if (gameState->currentRoom->IsRoomCleared())
		App::Print(800, 700, "Room Cleared");
	else
		App::Print(800, 700, "Room Not Cleared");

	/*PLAYER RENDER */
	auto player{ gameState->GetPlayer() };

	if (!player)
	{
		delete player;
		return;
	}
	App::Print(100, 400, ("Items : " + GetChar(gameState->currentRoom->GetActors().size())).c_str());
	App::Print(100, 300, GetChar(player->inventory->items[0].size()).c_str());

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);

	auto pos{ player->GetPosition() };
	auto string{ std::to_string(pos->x) + " " + std::to_string(pos->y) };

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
		float ms{ player->GetMovementSpeed() };
		if (player->GetDirection() == Direction::LEFT)
			ms = -player->GetMovementSpeed();
		auto actors{ gameState->currentRoom->GetActors()};
		try
		{
			if (actors.size() != 0)
			{
				std::vector<Actor*> interactiveActors{};
				for (auto & actor : actors)
					if (static_cast<Item*>(actor)->GetInteractivity() == Interactivity::Interactive)
						interactiveActors.emplace_back(actor);

				std::sort(std::begin(interactiveActors), std::end(interactiveActors), [player](Actor* const& l, Actor* const& r)
					{
						return 
							std::sqrt(std::pow(player->GetPosition()->x - l->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - l->GetPosition()->y, 2))
							< 
							std::sqrt(std::pow(player->GetPosition()->x - r->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - r->GetPosition()->y, 2));
					});

				App::Print(100, 600, ("Closest Interactive Item to Player : " + interactiveActors[0]->GetName()).c_str());
				if (player->GetCollider()->isColliding(player, interactiveActors[0], player->GetPosition()->x + ms, player->GetPosition()->y))
				{
					player->UseLighter(static_cast<Candle*>(interactiveActors[0]));
					auto item = static_cast<Page*>(interactiveActors[0]);
					if (item)
					{
						if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
						{
							player->inventory->items[0].emplace_back(item->Collect());
							if (gameState->currentRoom->RemoveActor(item))
							{
								App::Print(100, 500, ("Removed: " + interactiveActors[0]->GetName()).c_str());
							}
						}
					}
					/*if (player->inventory->AddItem(new InventoryItem(InventoryItem::Usability::Unusable, 0)))
						App::Print(300, 300, (interactiveActors[0]->GetName() + " added").c_str());
					else
						App::Print(300, 300, (interactiveActors[0]->GetName() + " not added").c_str());*/
				}

				for (auto actor : interactiveActors)
				{
					actor = nullptr;
					delete actor;
				}
			}
		}
		catch (const std::length_error& le)
		{
			App::Print(350, 450, le.what());
		}

		for (auto actor : actors)
		{
			actor = nullptr;
			delete actor;
		}
	}

	// Vertically
	if (player->GetDirection() == Direction::UP || player->GetDirection() == Direction::DOWN)
	{
		float ms{ player->GetMovementSpeed() };
		if (player->GetDirection() == Direction::DOWN)
			ms = -player->GetMovementSpeed();
		auto actors{ gameState->currentRoom->GetActors() };

		try
		{
			if (actors.size() != 0)
			{
				std::vector<Actor*> interactiveActors{};
				for (auto & actor : actors)
					if (static_cast<Item*>(actor)->GetInteractivity() == Interactivity::Interactive)
						interactiveActors.emplace_back(actor);

				std::sort(std::begin(interactiveActors), std::end(interactiveActors), [player](Actor* const& l, Actor* const& r)
					{
						return
							std::sqrt(std::pow(player->GetPosition()->x - l->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - l->GetPosition()->y, 2))
							<
							std::sqrt(std::pow(player->GetPosition()->x - r->GetPosition()->x, 2) + std::pow(player->GetPosition()->y - r->GetPosition()->y, 2));
					});

				App::Print(100, 600, ("Closest Interactive Item to Player : " + interactiveActors[0]->GetName()).c_str());
				if (player->GetCollider()->isColliding(player, interactiveActors[0], player->GetPosition()->x, player->GetPosition()->y + ms))
				{
					player->UseLighter(static_cast<Candle*>(interactiveActors[0]));
					/*if (player->inventory->AddItem(new InventoryItem(InventoryItem::Usability::Unusable, 0)))
						App::Print(300, 300, (interactiveActors[0]->GetName() + " added").c_str());
					else
						App::Print(300, 300, (interactiveActors[0]->GetName() + " not added").c_str());*/
				}
				for (auto actor : interactiveActors)
				{
					actor = nullptr;
					delete actor;
				}
			}
		}
		catch (const std::length_error& le)
		{
			App::Print(350, 450, le.what());
		}

		for (auto actor : actors)
		{
			actor = nullptr;
			delete actor;
		}
	}

	player = nullptr;
	delete player;
	pos = nullptr;
	delete pos;
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.²
//------------------------------------------------------------------------
void Shutdown()
{
}