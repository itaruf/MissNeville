#pragma once
#include <string>

struct DCharlotte 
{
	// Entrance
	std::string e1{ "[Charlotte Neville] says : Finally.. Someone here... Can you hear me... Can you see me ?! Fear not... My name is Charlotte Neville, unique daughter of the once proud Neville house ! This place is cursed, so am I.. my words cannot tell the truth on what happened here, but my journal can ! Unfortunatly, my family spreads its pages all throughout the mansion and locked them behind vicious and perfidious enigmas ! I beg you, you have to gather all of them to reach out the truth !" };

	// Hall
	std::string h1{ "[Charlotte Neville] says : A page from my journal must be around.. But it's so dark here ! M. Jones used to light everything up, but the darkness would never leave our family." };

	std::string h2{ "[Charlotte Neville] says : Poor M. Jones.. You were so loyal but you lost your way since.. the incident. That's one page, keep going !" };

	// Room
	std::string r1{ "[Charlotte Neville] says : Oh no..My beautiful mirror !The missing pieces should be all around the mansion, can you get all of them back ?" };

	std::string r2{ "[Charlotte Neville] says : My mirror, you repaired it and made her disappear ! Serves her right once again, haha !" };

	// Library
	std::string l1{ "[Charlotte Neville] says : Oh no ! my father moved everything in the library to prevent you from going any further... Knowing him, he might be thinking you are not smart enough to find another way !" };

	std::string l2{ "[Charlotte Neville] says : Father, you always were living for and by the books.. You would always tell others how precious were your books but you would never care for me.. Until I did. Oh I was just muttering to myself, That's another page collected !" };

	// Kitchen
	std::string k1{ "[Charlotte Neville] says : Mother, you always were living for and by the books.. You would always tell others how precious were your books but you would never care for me.. Until I did. " };
};

extern struct DCharlotte DCharlotte;

struct DJones
{
	// Hall
	std::string h1{ "[\"Bright\" Jones] says : No.. Do not light your path ..! Leave this cursed place while you can..! " };
};

extern struct DJones DJones;

struct DSmith
{
	// Room
	std::string r1{ "[Maggie Smith] says : It was no use.. A demon disguised as an angel could never be a true member of the highborn society..." };
};

extern struct DSmith DSmith;

struct DFather
{
	// Library
	std::string l1{ "[Ralph Neville] says : Why..? How could I not realized that the seed of evil was growing inside our glorious family..? Do not make the same mistake... Open your eyes and leave now ..!" };
};

extern struct DFather DFather;

struct DMother
{
	// Kitchen
	std::string k1{ "[Anne Neville] says : How could a mother be blind to the pain of their own child ..? This eternal punishment should be mine... But she decided to make it yours now..! You cannot escape this anymore..!" };
};

extern struct DMother DMother;

struct DDetective
{
	// Entrance
	std::string e1{ "[JJ Detective] says : Who are you.. What are you ?!" };

	std::string e2{ "[JJ Detective] says : Miss Neville ! I gathered all the missing pages from you journal, everyone will know the truth, everyone will know that you murdered all the members of your family and domestics !" };

	// Hall
	std::string h1{ "[JJ Detective] says : This place looks like a hall, I wonder the number of evidences I could get here." };

	// Room
	std::string r1{ "[JJ Detective] says : The mirror shattered in pieces !" };
	std::string r2{ "[JJ Detective] says : I need to find all the missing pieces... But why would they spread everywhere in the mansion ?" };

	// Library
	std::string l1{ "[JJ Detective] says : The library... but this is beyond anything I could ever imagine ! the tables are moving all by themselves, what is happening here ?!" };

	std::string l2{ "[JJ Detective] says : I do not belong to this place.. I have to gather them all faster and get out of here !" };

	// Kitchen
	std::string k1{ "[JJ Detective] says : Oh no, no... This was not supposed to be like this ! the mansion is trying to kill me !!" };
};

extern struct DDetective DDetective;

struct DIntro
{
	std::string i1{ "[...] says : We are in 1877, the tragedy of the Neville house, highborns in the english society found murdered in their mansion, still remains in the mind of the inhabitants, who now considerer the lands of the once proud family, cursed. No one could tell the reason of their deaths and since then, rumors started to spread. Some say ghosts of the former members still wander, waiting to take revenge, as they could not find peace... Some say spine-chilling screams and demoniac laughters can be heard from time to time from there... However, sayings without proof are superstitions.. But could there still be prooves after so long ? To step-in closer to the truth, you, JJ Detective, have decided to investigate the Neville's abandonned mansion once and for all..." };
};

extern struct DIntro DIntro;

struct DPage
{
	std::string p1{ "[Page 1] :" };
	std::string p2{ "[Page 2] :" };
	std::string p3{ "[Page 3] :" };
	std::string p4{ "[Page 4] :" };
};

extern struct DPage DPage;