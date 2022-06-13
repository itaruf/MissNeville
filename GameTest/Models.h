#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>

struct MTable
{
	std::string name{ "Table" };
	const char* model{ ".\\TestData\\Props\\table.bmp" };
	int frame{ 0 };
	float scale{ 1 };
};

extern struct MTable MTable;

struct MCommode
{
	std::string name{ "Commode" };
	const char* model{ ".\\TestData\\Props\\commode.bmp" };
	const char* model2{ ".\\TestData\\Props\\commode2.bmp" };
	const char* model3{ ".\\TestData\\Props\\commode3.bmp" };
	int frame{ 0 };
	float scale{ 2 };
	int frame2{ 0 };
	float scale2{ 2 };
	int frame3{ 0 };
	float scale3{ 2 };
};

extern struct MCommode MCommode;

struct MBed
{
	std::string name{ "Bed" };
	const char* model{ ".\\TestData\\Props\\bed.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MBed MBed;

struct MCandle
{
	std::string name{ "Candle" };
	const char* model{ ".\\TestData\\Props\\candle.bmp" };
	int frame{ 0 };
	float scale{ 0.5 };
};

extern struct MCandle MCandle;

struct MPentagramme
{
	std::string name{ "Pentagramme" };
	const char* model{ ".\\TestData\\Props\\pentagramme.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MPentagramme MPentagramme;

struct MCharlotte
{
	std::string name{ "Charlotte Neville" };
	const char* model{ ".\\TestData\\Characters\\charlotte.bmp" };
	int frame{ 1 };
	float scale{ 3 };
};

extern struct MCharlotte MCharlotte;

struct MFamily
{
	std::string name{ "Family" };
	const char* model{ ".\\TestData\\Characters\\family.bmp" };
	int frame{ 1 };
	float scale{ 3.5 };
};

extern struct MFamily MFamily;

struct MCarpet
{
	std::string name{ "Carpet" };
	const char* model{ ".\\TestData\\Props\\carpet-b.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MCarpet MCarpet;

struct MTriggerScene
{
	std::string name{ "Trigger Scene" };
	const char* model{ ".\\TestData\\Characters\\charlotte.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MTriggerScene MTriggerScene;

struct MWardrobe
{
	std::string name{ "Wardrobe" };
	const char* model{ ".\\TestData\\Props\\wardrobe.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MWardrobe MWardrobe;

struct MPage
{
	std::string name{ "Page" };
	const char* model{ ".\\TestData\\Props\\page.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MPage MPage;

struct MWall
{
	std::string name{ "Wall" };
	const char* model{ ".\\TestData\\Props\\.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MWall MWall;

struct MMirror
{
	std::string name{ "Mirror" };
	const char* model{ ".\\TestData\\Props\\mirror.bmp" };
	int frame{ 1 };
	float scale{ 0.25 };
};

extern struct MMirror MMirror;

struct MMirrorShard
{
	std::string name{ "Mirror Shard" };
	const char* model{ ".\\TestData\\Props\\.bmp" };
	int frame{ 0 };
	float scale{ 3 };
};

extern struct MMirrorShard MMirrorShard;

#endif // !MODEL_H