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
	/*subDialogues.clear();
	remainingDials = 0;
	start = 0;*/

	if (!_dialogueBox)
		return;

	speaker = Process(_currentDialogue, ':');
	auto line{ Process2(_currentDialogue, ':', false) };

	std::cout << speaker << std::endl;
	std::cout << line << std::endl;

	// If the dialogue to display is larger than the number of max characters allowed
	/*if (line.length() > maxChar)
	{*/
		auto nbSubDials{ std::ceil((double)line.length() / (double)maxChar) };
		/*auto nbTrunc{ std::trunc((double)line.length() / (double) maxChar) };*/

		App::Print(390, 315, GetChar(nbSubDials).c_str());

		auto start{ 0 };
		for (int i =  0 ; i < nbSubDials; i++)
		{
			subDialogues.emplace_back(line.substr(start, maxChar - 1));
			start = maxChar * (i + 1);
		}
	/*}*/


	if (subDialogues.size() > maxLines)
	{
		remainingDials = subDialogues.size();
		end = maxLines;
	}
	else
	{
		remainingDials = 0;
		end = subDialogues.size();
	}

	for (const auto& d : subDialogues)
		std::cout << d << std::endl;

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

			if (remainingDials < maxLines)
				end = start + remainingDials;
			else
				end = start + maxLines;
		}
		else
		{
			onDialogueEnd();
			StateMain::SetState(State::REGULAR);
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
		if (count >= maxLines)
			count = 0;

		App::Print(310, 100 - (count * 25), subDialogues[i].c_str());
		count++;
	}
}

void StateDialogue::Exit()
{
	subDialogues.clear();
	remainingDials = 0;
	start = 0;
}
