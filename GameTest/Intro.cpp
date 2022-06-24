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

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
	if (!stateDialogue)
		return;

	new Actor("Journal", App::CreateSprite(".\\TestData\\Backgrounds\\FlippingPages.bmp", 1, 1, 0, 3), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(0, 0, ColliderType::Overlap));

	stateDialogue->onDialogueEnd += [this]() { StateMain::LoadScene(5); };

	stateDialogue->_currentDialogue.emplace_back(DIntro.i1);
	StateMain::SetState(State::DIALOGUE);
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
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->onDialogueEnd.funcs.clear();
}

bool Intro::IsRoomCleared()
{
	return true;
}
