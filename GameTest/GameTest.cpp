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
#include "Collectable.h"
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

std::shared_ptr<GameState> gameState;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	gameState = std::make_shared<GameState>();
	gameState->currentRoom = new Entrance(0, gameState, nullptr);

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

	player = nullptr;
	vector = nullptr;
	collider = nullptr;
	inventory = nullptr;
	playerSprite = nullptr;
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
		
		// BAG 0
		if (App::IsKeyPressed('1') && !player->inventory->IsBagOpened(0) || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true) && !player->inventory->IsBagOpened(0))
			player->OpenInventory(0);

		else if (player->inventory->IsBagOpened(0))
		{
			if (App::IsKeyPressed('B') || App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
				player->CloseInventory(0);
			else if (App::IsKeyPressed('1') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
				player->GoToBagSlot(0, 0);
			else if (App::IsKeyPressed('2') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
				player->GoToBagSlot(0, 1);
			else if (App::IsKeyPressed('3') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
				player->GoToBagSlot(0, 2);
			else if (App::IsKeyPressed('4') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
				player->GoToBagSlot(0, 3);
		}

		// BAG 1
		if (App::IsKeyPressed('1') && !player->inventory->IsBagOpened(1) || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true) && !player->inventory->IsBagOpened(1))
			player->OpenInventory(1);

		else if (player->inventory->IsBagOpened(1))
		{
			if (App::IsKeyPressed('B') || App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
				player->CloseInventory(1);
			else if (App::IsKeyPressed('1') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
				player->GoToBagSlot(1, 0);
			else if (App::IsKeyPressed('2') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
				player->GoToBagSlot(1, 1);
			else if (App::IsKeyPressed('3') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
				player->GoToBagSlot(1, 2);
			else if (App::IsKeyPressed('4') || App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
				player->GoToBagSlot(1, 3);
		}
	}

	if (gameState->currentRoom)
		gameState->currentRoom->Update(deltaTime);
}

void Render()
{
	/*std::string(*ptr)(int);
	ptr = &returnInt;

	App::Print(700, 500, (*ptr)(5).c_str());*/
	
	/*********CURRENT ROOM RENDER*********/

	if (!gameState->currentRoom)
		return;

	gameState->currentRoom->Render();

	/*********PLAYER RENDER*********/

	auto player{ gameState->GetPlayer() };

	if (!player)
		return;

	player->GetSprite()->Draw();
	player->GetCollider()->DrawCollision(player, 50, 50, 50);

	auto pos{ player->GetPosition() };
	auto string{ std::to_string(pos->x) + " " + std::to_string(pos->y) };

	/*SOME PRINTS*/
	if (gameState->currentRoom->IsRoomCleared())
		App::Print(800, 700, "Room Cleared");
	else
		App::Print(800, 700, "Room Not Cleared");

	App::Print(200, 400, ("Items : " + GetChar(gameState->currentRoom->GetActors().size())).c_str());
	/*App::Print(200, 300, ("Page collected : " + GetChar(player->inventory->bags[0].second.size())).c_str());*/
	App::Print(100, 20, ("Player Pos: " + string).c_str());
	App::Print(800, 650, ("Player H (Spr): " + std::to_string(player->GetSprite()->GetHeight())).c_str());
	App::Print(800, 675, ("Player W (Spr): " + std::to_string(player->GetSprite()->GetWidth())).c_str());
	App::Print(800, 625, ("Player H (Col): " + std::to_string(player->GetCollider()->GetHeight())).c_str());
	App::Print(800, 600, ("Player W (Col): " + std::to_string(player->GetCollider()->GetWidth())).c_str());
	App::Print(800, 575, ("Player Name: " + player->GetName()).c_str());
	App::Print(900, 500, std::to_string(App::GetController().GetLeftThumbStickY()).c_str());
	App::Print(900, 450, std::to_string(App::GetController().GetLeftThumbStickX()).c_str());

	/*********PLAYER'S INTERACTIONS*********/

	auto actors{ gameState->currentRoom->GetActors() };
	if (actors.size() != 0)
	{
		std::vector<Actor*> interactiveActors{};
		for (auto& actor : actors)
			if (dynamic_cast<Collectable*>(actor) || dynamic_cast<IInteractive*>(actor))
				interactiveActors.emplace_back(actor);

		if (interactiveActors.size() > 0) 
		{
			/*SORT : FROM CLOSEST ACTOR TO FARTHEST*/
			std::sort(std::begin(interactiveActors), std::end(interactiveActors), [pos](Actor* const& l, Actor* const& r)
				{
					return
						std::sqrt(std::pow(pos->x - l->GetPosition()->x, 2) + std::pow(pos->y - l->GetPosition()->y, 2))
						<
						std::sqrt(std::pow(pos->x - r->GetPosition()->x, 2) + std::pow(pos->y - r->GetPosition()->y, 2));
				});


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
			
			auto closestActor = interactiveActors[0];

			App::Print(100, 600, ("Closest Item to Player : " + closestActor->GetName()).c_str());

			/*PLAYER CAN INTERACT WITH ITEMS ONLY IF HE COLLIDES WITH THEM*/
			if (player->GetCollider()->isColliding(player, closestActor, x, y))
			{
			
				/*INTERACT WITH NON COLLECTIBLE ITEMS*/
				auto tmp = dynamic_cast<IInteractive*>(closestActor);
				if (tmp)
				{
					player->Interact(tmp);
					return;
				}
				/*COLLECT ITEMS*/
				auto tmp2 = dynamic_cast<Collectable*>(closestActor);
				if (tmp2)
				{
					player->Interact(tmp2);
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