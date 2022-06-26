#include "../stdafx.h"
#include "Outro.h"

Outro::Outro(int ID) : Scene(ID)
{
}

Outro::~Outro()
{
}

void Outro::Init()
{
	if (initialized)
		return;

	Scene::Init();

	new Actor("Journal", App::CreateSprite(".\\TestData\\Backgrounds\\FlippingPages.bmp", 1, 1, 0, 3), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(0, 0, ColliderType::Overlap));

	/*auto blood{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 3, MBlood.frame, 10), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(0, 0, ColliderType::Overlap)) };
	blood->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BLOOD, 1 / 5.0f, { 0,1,2 }, true);
	blood->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BLOOD);*/

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(DOutro.o1);
	StateMain::SetState(State::DIALOGUE);
}

void Outro::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Outro::Render()
{
	Scene::Render();
}

void Outro::Exit()
{
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateMain::_stateControllers[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_onDialogueEnd.funcs.clear();
}

bool Outro::IsRoomCleared()
{
	return true;
}
