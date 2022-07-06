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

	auto b{ new Actor("Journal", App::CreateSprite("..\\..\\GameTest\\TestData\\Backgrounds\\theend.bmp", 5, 1, 5, 2), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(0, 0, ColliderType::Overlap)) };
	b->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BLOOD, 1 / 5.0f, { 0, 1, 2, 3, 4 }, true);
	b->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BLOOD);

	/*auto blood{ new Actor(MBlood.name, App::CreateSprite(MBlood.model, 1, 3, MBlood.frame, 10), new Vector2D(MIDDLE_WIDTH, MIDDLE_HEIGHT), new Collision(0, 0, ColliderType::Overlap)) };
	blood->GetSprite()->CreateAnimation(CSimpleSprite::ANIM_BLOOD, 1 / 5.0f, { 0,1,2 }, true);
	blood->GetSprite()->SetAnimation(CSimpleSprite::ANIM_BLOOD);*/

	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_currentDialogue.emplace_back(DOutro.o1);
	StateController::SetState(State::DIALOGUE);
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
	auto stateDialogue{ dynamic_cast<StateDialogue*>(StateController::_gameStates[2]) };
	if (!stateDialogue)
		return;

	stateDialogue->_onDialogueEnd.funcs.clear();
}

bool Outro::IsRoomCleared()
{
	return true;
}
