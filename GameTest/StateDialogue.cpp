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
	size_t pos{ line.find(" ", 1) };

	std::cout << pos << std::endl;
	if (pos == std::string::npos)
		ForceLineWrap(line);

	else
		LineWrap(line, pos);
}

void StateDialogue::Clear()
{
	subDialogues.clear();
	remainingDials = 0;
	start = 0;
}

void StateDialogue::ForceLineWrap(std::string line)
{
	std::cout << "HERE" << std::endl;
	std::cout << line << std::endl;
	auto start{ 0 };
	auto nbSubDials{ std::ceil((double)line.length() / (double)maxChar) };

	for (int i = 0; i < nbSubDials; i++)
	{
		subDialogues.emplace_back(line.substr(start, maxChar));
		std::cout << line.substr(start, maxChar) << std::endl;
		std::cout << line.substr(start, maxChar).size() << std::endl;
		start = maxChar * (i + 1);
	}

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

void StateDialogue::LineWrap(std::string dialogue, size_t pos)
{
	auto start{ 0 };
	auto length{ dialogue.length() };
	auto count{ 0 };

	do
	{
		if (length <= maxChar)
		{
			subDialogues.emplace_back(dialogue);
			std::cout << dialogue << std::endl;
			break;
		}

		pos = dialogue.find(" ", pos + 1);
		count = pos - start;

		// if the an entire word is within the character limitation
		if (count >= maxChar)
		{
			subDialogues.emplace_back(dialogue.substr(start, count));
			start = pos;
		}

		if (pos > length)
		{
			subDialogues.emplace_back(dialogue.substr(start, pos));
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
