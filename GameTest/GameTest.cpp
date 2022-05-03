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
//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite;
CSimpleSprite *testSprite2;
CSimpleSprite* testSprite3;

// Actors - Characters
std::shared_ptr<Actor> item;
std::shared_ptr<Actor> item2;
std::shared_ptr<Character> player;

std::unique_ptr<CSimpleSprite> imaneSprite;

std::string message = " ";
std::string inputmessage = " ";
std::string debug = " ";
std::shared_ptr<Room> currentRoom = std::make_shared<Room>(1);
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	/*Instantiation du personnage*/
	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	Vector2D vector{ 900.0f, 400.0f };
	Collision* collider = new Collision(Collision::ColliderType::Block, 1, 1);
	player = std::make_shared<Character>("Imane", testSprite, vector, collider, currentRoom.get(), 20, 5);

	/*currentRoom->AddActor(player.get());*/
	/*Caractéristiques de bases*/
	player->GetCollider()->SetHeight(5);
	player->GetCollider()->SetWidth(10);
	player->GetName() = "test";
	player->GetHP() = 50;
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_BACKWARDS, 1.0f / 15.0f, { 0,1,2,3,4,5,6,7 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_LEFT, 1.0f / 15.0f, { 8,9,10,11,12,13,14,15 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_RIGHT, 1.0f / 15.0f, { 16,17,18,19,20,21,22,23 });
	player->GetSprite()->CreateAnimation(player->GetSprite()->ANIM_FORWARDS, 1.0f / 15.0f, { 24,25,26,27,28,29,30,31 });
	player->GetSprite()->SetScale(1.0f);

	testSprite2 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite2->SetFrame(2);
	testSprite2->SetScale(0.5f);

	testSprite3 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite3->SetFrame(2);
	testSprite3->SetScale(0.5f);

	player->SetSprite(testSprite);

	Vector2D vector2{ 400.0f, 400.0f };
	Collision* collider2 = new Collision(Collision::ColliderType::Block, 2, 2);

	item = std::make_shared<Actor>("Item1", testSprite2, vector2, collider2, currentRoom.get());

	Vector2D vector3{ 400.f, 200.f };
	Collision* collider3 = new Collision(Collision::ColliderType::Block, 2, 2);

	item2 = std::make_shared<Actor>("Item2", testSprite3, vector3, collider3, currentRoom.get());

	currentRoom->AddActor(item.get());
	currentRoom->AddActor(item2.get());
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	player->GetSprite()->Update(deltaTime);
	testSprite2->Update(deltaTime);

	player->isMoving();
	player->MoveHorizontally();
	player->MoveVertically();

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		player->GetSprite()->SetScale(player->GetSprite()->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		player->GetSprite()->SetScale(player->GetSprite()->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		player->GetSprite()->SetAngle(player->GetSprite()->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		player->GetSprite()->SetAngle(player->GetSprite()->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		player->GetSprite()->SetAnimation(-1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		player->GetSprite()->SetVertex(0, player->GetSprite()->GetVertex(0) + 5.0f);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}

	player->GetSprite()->Draw();
	testSprite2->Draw();
	testSprite3->Draw();

	App::Print(700, 600, inputmessage.c_str());
	App::Print(700, 400, message.c_str());

	auto string = std::to_string(player->GetPosition().x) + " " + std::to_string(player->GetPosition().y);

	float x, y;
	player->GetSprite()->GetPosition(x, y);

	auto pos = player->GetPosition();
	auto string2 = std::to_string(pos.x) + " " + std::to_string(pos.y);

	App::Print(100, 0, string.c_str());
	App::Print(100, 20, string2.c_str());
	App::Print(500, 500, std::to_string(player->GetHP()).c_str());
	App::Print(500, 550, std::to_string(player->GetSprite()->GetHeight()).c_str());
	App::Print(500, 575, std::to_string(player->GetSprite()->GetWidth()).c_str());
	App::Print(600, 500, std::to_string(player->GetCollider()->GetHeight()).c_str());
	App::Print(600, 500, std::to_string(player->GetCollider()->GetWidth()).c_str());
	App::Print(700, 500, player->GetName().c_str());
	App::Print(900, 500, std::to_string(App::GetController().GetLeftThumbStickY()).c_str());
	App::Print(900, 450, std::to_string(App::GetController().GetLeftThumbStickX()).c_str());
	App::Print(0, 500, std::to_string(currentRoom->GetActor(0)->GetPosition().x).c_str());
	/*App::Print(50, 100, std::to_string(player->GetCurrentRoom()->GetActors().size()).c_str());*/

	for (int i = 0; i < currentRoom->GetActors().size(); i++)
	{
		App::Print(100 + i*50, 500, currentRoom->GetActor(i)->GetName().c_str());
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		/*player->SetSprite(testSprite2);*/
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	delete testSprite2;
	//------------------------------------------------------------------------
}