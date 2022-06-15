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

	auto speaker{ Process(_currentDialogue, ':') };
	auto line{ Process2(_currentDialogue, ':', false) };

	// If the dialogue to display is larger than the number of max characters allowed
	if (line.length() > maxChar)
	{
		auto nbSubDials{ std::ceil((double) line.length() / (double) maxChar)};
		App::Print(390, 315, GetChar(nbSubDials).c_str());
		
		auto start{ 0 };
		for (auto i{ 0 }; i < (int)nbSubDials; ++i)
		{
			subDialogues.emplace_back(line.substr(start , static_cast<__int64>(maxChar) * static_cast<__int64>(i + 1)));
			App::Print(390, 340 + i * 25, subDialogues[i].c_str());
			start = maxChar * (i + 1);
		}
	}

	App::Print(390, 300, GetChar(line.length()).c_str());

	App::Print(390, 135, speaker.c_str());
	for (auto i{ 0 }; i < subDialogues.size(); ++i)
	{
		App::Print(310, 100 - (i * 25), subDialogues[i].c_str());
	}

	subDialogues.clear();
}

void StateDialogue::Exit()
{
}
