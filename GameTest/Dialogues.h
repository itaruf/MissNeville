#pragma once
#include <string>

struct DCharlotte 
{
	// Entrance
	std::string e1{ "Finally.. Someone here... Can you hear me... Can you see me ?! Fear not... My name is Charlotte Neville, unique daughter of the once proud Neville house ! This place is cursed, so am I.. my words cannot tell the truth on what happened here, but my journal can ! Unfortunatly, my family spreads its pages all throughout the mansion and locked them behind vicious and perfidious enigmas ! I beg you, you have to gather all of them to reach out the truth !" };

	// Hall
	std::string h1{ "A page from my journal must be around.. But it's so dark here ! M. Jones used to light everything up, but the darkness would never leave our family." };

	std::string h2{ "Poor M. Jones.. You were so loyal but you lost your way since.. the incident. That's one page, keep going !" };

	// Room
	std::string r1{ "My mirror, you repaired it and made her disappear ! Serves her right once again, haha !" };

	// Library
	std::string l1{ "Father, you always were living for and by the books.. You would always tell others how precious were your books but you would never care for me.. Until I did." };

	// Kitchen
	std::string k1{ "Mother, you always were living for and by the books.. You would always tell others how precious were your books but you would never care for me.. Until I did. " };
};

struct DJones
{
	// Hall
	std::string h1{ "No.. Do not light your path ..! Leave this cursed place while you can..! " };
};

struct DSmith
{
	// Room
	std::string r1{ "It was no use.. A demon disguised as an angel could never be a true member of the highborn society..." };
};

struct DFather
{
	// Library
	std::string l1{ "Why..? How could I not realized that the seed of evil was growing inside our glorious family..? Do not make the same mistake... Open your eyes and leave now ..!" };
};

struct DMother
{
	// Kitchen
	std::string k1{ "How could a mother be blind to the pain of their own child ..? This eternal punishment should be mine... But they decided to make it yours now..! You cannot escape this anymore..!" };
};

struct DDetective
{
	// Entrance
	std::string e1{ "Who are you.. What are you ?!" };

	std::string e2{ "Miss Neville ! I gathered all the missing pages from you journal, everyone will know the truth, everyone will know that you murdered all the members of your family and domestics !" };

	// Hall
	std::string h1{ "This place looks like a hall, I wonder the number of evidences I could get here." };

	// Room
	std::string r1{ "The mirror shattered in pieces !" };
	std::string r2{ "I need to find all the missing pieces... But why would they spread everywhere in the mansion ?" };

	// Library
	std::string l1{ "The library... but this is beyond anything I could ever imagine ! the tables are moving all by themselves, what is happening here ?!" };

	// Kitchen
	std::string k1{ "Oh no, no... This was not supposed to be like this ! the mansion is trying to kill me !!" };
};

struct DIntro
{
	std::string i1{ "[...] says : We are in 1877, the tragedy of the Neville house, highborns in the english society found murdered in their mansion, still remains in the mind of the inhabitants, who now considerer the lands of the once pround family, cursed. Some says ghosts of the former members still wander to protect their secrets. Some says spine-chilling screams and demoniac laughters can be heard from there. However, sayings without proof are superstitions.. But Could there still be prooves to step-in closer to the truth ? You, JJ Detective, have decided to investigate the place once and for all..." };
};

extern struct DIntro DIntro;