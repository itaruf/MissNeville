#include "../stdafx.h"
#include "Intro.h"

Intro::Intro(int ID) : Scene(ID)
{
}

Intro::~Intro()
{
}

void Intro::Init()
{
	if (initialized)
		return;

	Scene::Init();

	new Actor("Journal", App::CreateSprite("..\\..\\GameTest\\TestData\\Backgrounds\\FlippingPages.bmp", 1, 1, 0, 3), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(0, 0, ColliderType::Overlap));

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_onDialogueEnd += [this]() { StateController::LoadScene(5); };
	stateDialogue->_currentDialogue.emplace_back(DIntro.i1);

	StateController::SetState(State::DIALOGUE);
}

void Intro::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Intro::Render()
{
	Scene::Render();
}

void Intro::Exit()
{
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_onDialogueEnd.funcs.clear();
}

bool Intro::IsRoomCleared()
{
	return true;
}
