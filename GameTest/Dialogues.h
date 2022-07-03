#pragma once
#include <string>

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

struct DCharlotte
{
	// Entrance
	std::string e1{ "[Charlotte Neville] says : Finally.. Someone here... Can you hear me... Can you see me ?! Fear not... My name is Charlotte Neville, unique daughter of the once proud Neville house ! This place is cursed, so am I.. my words cannot tell the truth on what happened here, but my journal can ! Unfortunatly, my family spreads its pages all throughout the mansion and locked them behind vicious and perfidious enigmas ! I beg you, you have to gather all of them to reach out to the truth !" };

	std::string e2{ "[Charlotte Neville] says : Very well ! I shall act as your guide then !" };

	std::string e3{ "[Charlotte Neville] says : Let us work together !" };
	// Hall
	std::string h1{ "[Charlotte Neville] says : A page from my journal must be around.. But it's so dark here ! M. Jones used to light everything up, but the darkness would never leave our family." };

	std::string h2{ "[Charlotte Neville] says : Poor M. Jones.. You were so loyal but you lost your way since.. the incident. That's one page, keep going !" };

	// Room
	std::string r1{ "[Charlotte Neville] says : Oh no... My beautiful mirror, why would you do this, Ms. Smith ?! The missing pieces should be all around the mansion, can you get all of them back ?" };

	std::string r2{ "[Charlotte Neville] says : My mirror ! you repaired it but also made her disappear ! Serves her right once again, hehe ! What's that look on your face ? Look at it in the mirror, hehe !" };

	// Library
	std::string l1{ "[Charlotte Neville] says : Oh no ! my father moved everything in the library to prevent you from going any further... Knowing him, he might be thinking you are not smart enough to find another way !" };

	std::string l2{ "[Charlotte Neville] says : Father, you always were living for and by the books.. You would always tell others how precious were your books but you would never care for me.. Until I did. Oh ! I was just muttering to myself, That's another page collected !" };

	// Kitchen
	std::string k1{ "[Charlotte Neville] says : Watch out ! Mother is trying to heavely injure you ! But there still might be a way to stop all this... Try turning off anything you can !" };

	std::string k2{ "[Charlotte Neville] says : Your little and cheap tricks did not work on us ! Take your second punishment for being such a bad mother ! Haha ! Let us move on, there's only one page left !" };

	//Outro
	std::string o1{ "[Charlotte Neville] says : Where do you think you are going, M. \"detective\" ? " };

	std::string o2{ "[Charlotte Neville] says : Hehe ! Yes, it was me all along... Because you cleared every obstacles I put in your way, I'am willing to tell you more : the Neville house used to be a well-respected family in the english society and thus, we, members of it, had to show that we were worthy of bearing its name. However, this was not what I wanted : I wanted to be free, and this cursed family would not allow me to be so, so... I decided to dispose of aaaaaall of them without exception and how it felt great, hehe ! And what happened afterwards was even greater : to reward my will of freedom, the \"Great Evil\" granted me necromantic powers under the condition to leave my physical shape behind and swear absolute loyalty with my soul to them !" };

	std::string o3{ "[Charlotte Neville] says : Now now, the fun has just begun... Right, \"detective\" ? Well, what shall I do with you... Oh ! I know, I was just in need of another servant and I think you'll be perfect for this !" };

	std::string o4{ "[Charlotte Neville] says : Nobody escapes from this place in one piece ! Now, I shall prepare the playground for the next toy to come and you'll be there, welcoming them, hehehe !" };
};

extern struct DCharlotte DCharlotte;

struct DDetective
{
	// Entrance
	std::string e1{ "[JJ Detective] says : Who are you.. What are you ?!" };
	std::string e2{ "[JJ Detective] says : I guess some rumors were true after all, there are ghosts here.. Anyway, as long as you do not interfere with my investigation, so be it."};

	// Hall
	std::string h1{ "[JJ Detective] says : This place looks like a hall, I wonder the number of evidences I could get here." };

	// Room
	std::string r1{ "[JJ Detective] says : The mirror shattered in pieces !" };
	std::string r2{ "[JJ Detective] says : I need to find all the missing pieces... But why would they spread everywhere in the mansion ?" };
	std::string r3{ "[JJ Detective] says : I finally have everything I needed... I have to get out of here now !" };
	std::string r4{ "[JJ Detective] says : The mirror is intact..." };

	// Library
	std::string l1{ "[JJ Detective] says : The library... but this is beyond anything I could ever imagine ! the tables are moving all by themselves, what is happening here ?!" };

	std::string l2{ "[JJ Detective] says : I do not belong to this place.. I have to gather them all faster and get out of here !" };

	// Kitchen
	std::string k1{ "[JJ Detective] says : Oh no, no... This was not supposed to be like this ! the mansion is trying to kill me !!" };

	std::string k2{ "[JJ Detective] says : It seems that I have almost collected all the missing pages... I need to gather my thoughts : I am so close to the truth !" };

	// Outro
	std::string o1{ "[JJ Detective] says : Miss Neville ! I gathered all the missing pages from your journal, now, everyone will know the truth, everyone will know that you murdered all the members of your family and your domestics ! Your name will forever remain cursed by the people !" };

	std::string o2{ "[JJ Detective] says : At the end, you only were a little brat. Playtime is over, Farewell." };

	std::string o3{ "[JJ Detective] says : What ? I cannot move anymore, what are you doing ?! Noooo..!" };
};

extern struct DDetective DDetective;

struct DIntro
{
	std::string i1{ "[...] says : We are in 1877, the tragedy of the Neville house, highborns in the english society found murdered in their mansion, still remains in the mind of the inhabitants, who now considerer the lands of the once proud family, cursed. No one could tell the reason of their deaths and since then, rumors started to spread. Some say ghosts of the former members still wander, waiting to take revenge... Some say spine-chilling screams and demoniac laughters can be heard from time to time from there... However, sayings without proof are superstitions.. But could there still be evidence after so long ? To step-in closer to the truth, you, JJ Detective, have decided to investigate the Neville's abandonned mansion once and for all..." };
};

extern struct DIntro DIntro;

struct DOutro
{
	std::string o1{ "[...] says : Following the mysterious disappearance of JJ Detective who went to investigate the Neville house, nobody tried to look for him and thus, the mystery of the Neville house aswell as the numerous rumors surrounding it continued to spread among the people..." };
};

extern struct DOutro DOutro;

struct DProps
{
	std::string p1{ "[Page 1] : Dear diary,\nToday's the same day as always.\nOur governess, Ms. Smith, scolded me all day for not behaving like a \"proper english lady\" or so she says..\nIt is always : \"Charlotte ! do not do this !\" or \"No.. Charlotte ! do not say this, say that instead !\", it is so frustrating !\nI cannot believe Father and Mother hired this pig to teach me how to behave ! Oh ! Ms. Pig better not read this or she is going to grunt with her pig nose wiiiiide open hehe !\nBlessed be the day she finally leaves our house ! I am hearing M. Jones coming this way, he can be a bit annoying but he still is kind ! - Charlotte Neville." };
	std::string p2{ "[Page 2] : That's enough, Father is the worst of all, he does not care about me as a person, he only cares about me when I am his good obediant daughter, and when I am not, I am no more than that unworthy girl who needs to be corrected. That's my life. Why can't I be a teenager like ordinary people... I just want to do whatever my mind is telling me but Father restrains everything... No, that's not only him, it's every. single. damn. members of my family. This needs to change, I will not let them dictate my life !! - Charlotte." };
	std::string p3{ "[Page 3] : Earlier in the day, I picked up a book in the library which had a bizarre and shiny symbol on its cover... Like... a star ? Back in my room, as I opened it, A strange form came off of it and... talked to me ! I do not know for certain what it said but... I felt something, I felt like I had to reach true freedom. At that moment, it became a certainty : my family is an obstacle to my freedom and I shall break my chains now ! - Charlotte." };
	std::string p4{ "[Page 4] : Deaaar diary, this is the last time I am writing as I finally reached total freedom ! Therefore, it will not be necessary to hide my thoughts as I can express them loud and clear ! hehe ! Dress unproperly ? Done ! Badmouthing ? Done ! Ah ! it feels a bit strange having nobody yelling at you everytime you talk or move... Anyway that shadowy form seems to have projects for me so farewell ! - Charlotte" };
	std::string m{ "[...] : A sharp mirror shard." };
};

extern struct DProps DProps;