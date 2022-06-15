#include "../stdafx.h"
#include "StateDialogue.h"

StateDialogue::StateDialogue(CSimpleSprite* dialogueBox) : _dialogueBox{dialogueBox}
{
}

StateDialogue::~StateDialogue()
{
	if (_dialogueBox)
		delete _dialogueBox;
}

void StateDialogue::Enter()
{
}

void StateDialogue::Update()
{
}

void StateDialogue::Render()
{
	/*_currentDialogue.c_str()*/

	if (!_dialogueBox)
		return;

	_dialogueBox->Draw();


	std::cout << _currentDialogue.length() << std::endl;
	App::Print(390, 135, Process(_currentDialogue, ':').c_str());
	App::Print(100, 100, Process2(_currentDialogue, ':', false).c_str());
}

void StateDialogue::Exit()
{
}
