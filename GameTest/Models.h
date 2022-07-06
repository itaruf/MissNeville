#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>

struct MBackground
{
	std::string name{ "Background" };
	const char* model{ "..\\..\\GameTest\\TestData\\Backgrounds\\background.bmp" };
	const char* model2{ "..\\..\\GameTest\\TestData\\Backgrounds\\background3.bmp" };
	const char* model3{ "..\\..\\GameTest\\TestData\\Backgrounds\\background4.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MBackground MBackground;

struct MTable
{
	std::string name{ "Table" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\table.bmp" };
	const char* model3{ "..\\..\\GameTest\\TestData\\Props\\table3.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MTable MTable;

struct MCommode
{
	std::string name{ "Commode" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\commode.bmp" };
	const char* model2{ "..\\..\\GameTest\\TestData\\Props\\commode2.bmp" };
	const char* model3{ "..\\..\\GameTest\\TestData\\Props\\commode3.bmp" };
	const char* model6{ "..\\..\\GameTest\\TestData\\Props\\commode6.bmp" };
	const char* model7{ "..\\..\\GameTest\\TestData\\Props\\commode7.bmp" };
	int frame{ 0 };
	float scale{ 2.5 };
	float scale2{ 2 };
	float scale3{ 2 };
	float scale4{ 1 };
};

extern struct MCommode MCommode;

struct MShelf
{
	std::string name{ "Shelf" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\shelf.bmp" };
	const char* model6{ "..\\..\\GameTest\\TestData\\Props\\shelf6.bmp" };
	int frame{ 0 };
	float scale{ 2 };
	float scale2{ 2.5 };
	float scale3{ 2.5 };
	float scale4{ 1 };
	float scale5{ 1 };
	float scale6{ 1 };
};

extern struct MShelf MShelf;

struct MWeb
{
	std::string name{ "Spider Web" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\web.bmp" };
	const char* model2{ "..\\..\\GameTest\\TestData\\Props\\web2.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MWeb MWeb;

struct MBook
{
	std::string name{ "Book" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\booksheet.bmp" };
	int frame{ 12 };
	float scale{ 2 };
};

extern struct MBook MBook;


struct MBed
{
	std::string name{ "Bed" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\bed.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MBed MBed;

struct MCandle
{
	std::string name{ "Candle" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\candles.bmp" };
	int frame{ 0 };
	int frame2{ 1 };
	float scale{ 2 };
};

extern struct MCandle MCandle;

struct MPentagramme
{
	std::string name{ "Pentagramme" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\pentagramme.bmp" };
	int frame{ 5 };
	float scale{ 1 };
};

extern struct MPentagramme MPentagramme;

struct MCharlotte
{
	std::string name{ "Charlotte Neville" };
	const char* model{ "..\\..\\GameTest\\TestData\\Characters\\charlotte.bmp" };
	int frame{ 1 };
	float scale{ 3 };
};

extern struct MCharlotte MCharlotte;

struct MFamily
{
	std::string name{ "Family" };
	const char* model{ "..\\..\\GameTest\\TestData\\Characters\\ghost.bmp" };
	int frame{ 1 };
	float scale{ 3 };
};

extern struct MFamily MFamily;

struct MCarpet
{
	std::string name{ "Carpet" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\carpet-b.bmp" };
	int frame{ 0 };
	float scale{ 3 };
	float scale2{ 2 };
};

extern struct MCarpet MCarpet;

struct MTriggerScene
{
	std::string name{ "Trigger Scene" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\door.bmp" };
	int frame{ 0 };
	float scale{ 1.5 };
};

extern struct MTriggerScene MTriggerScene;

struct MWardrobe
{
	std::string name{ "Wardrobe" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\wardrobe.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MWardrobe MWardrobe;

struct MPage
{
	std::string name{ "Page" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\page.bmp" };
	const char* model2{ "..\\..\\GameTest\\TestData\\Props\\papers.bmp" };
	int frame{ 0 };
	float scale{ 3 };
	float scale2{ 2 };
};

extern struct MPage MPage;

struct MSkull
{
	std::string name{ "skull" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\skull.bmp" };
	const char* model2{ "..\\..\\GameTest\\TestData\\Props\\skulls.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MSkull MSkull;

struct MWall
{
	std::string name{ "Wall" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MWall MWall;

struct MMirror
{
	std::string name{ "Mirror" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\mirror.bmp" };
	int frame{ 0 };
	float scale{ 1 };
};

extern struct MMirror MMirror;

struct MMirrorShard
{
	std::string name{ "Mirror Shard" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MMirrorShard MMirrorShard;

struct MPillar
{
	std::string name{ "Pillar" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\pillar2.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MPillar MPillar;

struct MStairs
{
	std::string name{ "Stairs" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\stairs.bmp" };
	int frame{ 0 };
	float scale{ 4 };
};

extern struct MStairs MStairs;

struct MRailing
{
	std::string name{ "Railing" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\railing.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MRailing MRailing;

struct MPicture
{
	std::string name{ "Picture" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\picture.bmp" };
	const char* model2{ "..\\..\\GameTest\\TestData\\Props\\picture2.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MPicture MPicture;

struct MIcon
{
	std::string name{ "Icon" };
	const char* model{ "..\\..\\GameTest\\TestData\\Icons\\question_mark.bmp" };
	int frame{ 0 };
	float scale{ 1.5 };
};

extern struct MIcon MIcon;

struct MLamp
{
	std::string name{ "Lamp" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\lamp.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MLamp MLamp;

struct MKnife
{
	std::string name{ "Axe" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\knife.bmp" };
	int frame{ 0 };
	float scale{ 4 };
};

extern struct MKnife MKnife;

struct MOven
{
	std::string name{ "Oven" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\oven.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MOven MOven;

struct MBarrel
{
	std::string name{ "Barrel" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\barrels.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MBarrel MBarrel;

struct MBag
{
	std::string name{ "Bag" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\bags.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MBag MBag;

struct MPot
{
	std::string name{ "Pot" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\boil.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MPot MPot;

struct MFire
{
	std::string name{ "Fire" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\fire2.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MFire MFire;

struct MCell
{
	std::string name{ "Cell" };
	const char* model{ "..\\..\\GameTest\\TestData\\Props\\cell.bmp" };
	int frame{ 0 };
	float scale{ 2 };
};

extern struct MCell MCell;

struct MBlood
{
	std::string name{ "Blood" };
	const char* model{ "..\\..\\GameTest\\TestData\\VFX\\blood.bmp" };
	int frame{ 0 };
	float scale{ 2 };
	float scale2{ 1 };
};

extern struct MBlood MBlood;

struct MArrow
{
	std::string name{ "Arrow" };
	const char* left{ "..\\..\\GameTest\\TestData\\Icons\\arrow_left.bmp" };
	const char* right{ "..\\..\\GameTest\\TestData\\Icons\\arrow_right.bmp" };
	const char* up{ "..\\..\\GameTest\\TestData\\Icons\\arrow_up.bmp" };
	const char* down{ "..\\..\\GameTest\\TestData\\Icons\\arrow_down.bmp" };
	int frame{ 0 };
	float scale{ 1 };
};

extern struct MArrow MArrow;

struct SFX
{
	const char* entrance{ "..\\..\\GameTest\\TestData\\SFX\\entrance.wav" };
	const char* mshard_pick{ "..\\..\\GameTest\\TestData\\SFX\\mshard_pick.wav" };
	const char* mirror_broken{ "..\\..\\GameTest\\TestData\\SFX\\mirror_broken.wav" };
	const char* mirror_repaired{ "..\\..\\GameTest\\TestData\\SFX\\item_pick.wav" };
	const char* candle_enlight{ "..\\..\\GameTest\\TestData\\SFX\\candle_enlight.wav" };
	const char* item_pick{ "..\\..\\GameTest\\TestData\\SFX\\item_pick.wav" };
	const char* item_pick2{ "..\\..\\GameTest\\TestData\\SFX\\item_pick2.wav" };
	const char* ghost_death{ "..\\..\\GameTest\\TestData\\SFX\\ghost_death.wav" };
	const char* door_open{ "..\\..\\GameTest\\TestData\\SFX\\door_open.wav" };
	const char* scene{ "..\\..\\GameTest\\TestData\\SFX\\scene.wav" };
	const char* bag_open{ "..\\..\\GameTest\\TestData\\SFX\\bag_open.wav" };
	const char* bag_navigate{ "..\\..\\GameTest\\TestData\\SFX\\bag_navigate.wav" };
	const char* footstep{ "..\\..\\GameTest\\TestData\\SFX\\footstep.wav" };
	const char* footstep2{ "..\\..\\GameTest\\TestData\\SFX\\footstep2.wav" };
	const char* page_read{ "..\\..\\GameTest\\TestData\\SFX\\page_read.wav" };
	const char* tp_sound{ "..\\..\\GameTest\\TestData\\SFX\\tp_sound.wav" };
};

extern struct SFX SFX;

struct MMessage
{
	std::string door_unlocked{ "[...] : You hear a door opening..." };
	std::string door_locked{ "[...] : You hear a door closing..." };
};

extern struct MMessage MMessage;


#endif // !MODEL_H

//CSimpleSound::GetInstance().PlaySoundW(_SEnlight, 0);