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
	if (!_dialogueBox)
		return;

	Clear();

	ProcessDialogue(_currentDialogue[0]);
}

void StateDialogue::Update()
{
	// Check if there are more dialogues
	if (App::IsKeyPressed(VK_SPACE) || App::GetController().CheckButton(XINPUT_GAMEPAD_A))
	{
		CSimpleSound::GetInstance().PlaySoundW(SFX.page_read, 0);

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
			_currentDialogue.erase(_currentDialogue.begin());

			if (_currentDialogue.empty())
			{
				StateController::SetState(State::REGULAR);
				_onDialogueEnd();
			}
			else
				ProcessDialogue(_currentDialogue[0]);
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
	Clear();
}

void StateDialogue::ProcessDialogue(std::string dialogue)
{
	Clear();

	speaker = Process(dialogue, ':');
	auto line{ Process2(dialogue, ':', false) };

	auto start{ 0 };
	auto length{ line.length() };
	size_t pos{ line.find(" ") };
	auto count{ 0 };

	do
	{
		if (length <= maxChar)
		{
			subDialogues.emplace_back(line);
			std::cout << line << std::endl;
			break;
		}

		pos = line.find(" ", pos + 1);
		count = pos - start;

		// if the an entire word is within the character limitation
		if (count >= maxChar)
		{
			subDialogues.emplace_back(line.substr(start, count));
			start = pos;
		}

		if (pos > length)
		{
			subDialogues.emplace_back(line.substr(start, pos));
			break;
		}

	} while (true);

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
}

void StateDialogue::Clear()
{
	subDialogues.clear();
	remainingDials = 0;
	start = 0;
}
