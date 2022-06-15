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
	subDialogues.clear();
	remainingDials = 0;
	start = 0;

	if (!_dialogueBox)
		return;

	speaker = Process(_currentDialogue, ':');
	auto line{ Process2(_currentDialogue, ':', false) };

	// If the dialogue to display is larger than the number of max characters allowed
	if (line.length() > maxChar)
	{
		auto nbSubDials{ std::ceil((double)line.length() / (double)maxChar) };
		auto nbTrunc{ std::trunc((double)line.length() / (double) maxChar) };

		std::cout << nbSubDials << std::endl;
		std::cout << nbTrunc << std::endl;

		App::Print(390, 315, GetChar(nbSubDials).c_str());

		auto start{ 0 };
		for (int i =  0 ; i < nbSubDials; i++)
		{
			/*std::cout << "current start:  " << start << std::endl;*/

			subDialogues.emplace_back(line.substr(start, maxChar));
			std::cout << "[LINE] : " << line.substr(start, maxChar) << std::endl;

			/*std::cout << subDialogues[i] << std::endl;*/
			/*std::cout << "next start:  " << start << std::endl;*/

			start = maxChar * (i + 1);
		}
	}

	remainingDials = subDialogues.size();
	end = maxLines;

	std::cout << remainingDials << std::endl;
	std::cout << line.length() << std::endl;
}

void StateDialogue::Update()
{
	// Check if there are more dialogues
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
	{
		if (remainingDials > maxLines)
		{
			start += maxLines;
			remainingDials -= maxLines;
			end = maxLines + remainingDials;
		}
	}
}

void StateDialogue::Render()
{
	if (!_dialogueBox)
		return;

	_dialogueBox->Draw();

	App::Print(390, 135, speaker.c_str());
	int count{ 0 };
	for (auto i{ start }; i < end; ++i)
	{
		App::Print(310, 100 - (count * 25), subDialogues[i].c_str());
		count++;
	}
}

void StateDialogue::Exit()
{
	remainingDials = 0;
	start = 0;
}
