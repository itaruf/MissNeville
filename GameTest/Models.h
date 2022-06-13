#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>

struct MTable
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MTable::name{ "Table" };
const char* MTable::model{ ".\\TestData\\Props\\table.bmp" };
int MTable::frame{ 0 };
float MTable::scale{ 1 };

struct MCommode
{
	static std::string name;
	static const char* model;
	static const char* model2;
	static const char* model3;
	static int frame;
	static float scale;
	static int frame2;
	static float scale2;	
	static int frame3;
	static float scale3;
};

std::string MCommode::name{ "Commode" };
const char* MCommode::model{ ".\\TestData\\Props\\commode.bmp" };
const char* MCommode::model2{ ".\\TestData\\Props\\commode2.bmp" };
const char* MCommode::model3{ ".\\TestData\\Props\\commode3.bmp" };
int MCommode::frame{ 0 };
float MCommode::scale{ 2 };
int MCommode::frame2{ 0 };
float MCommode::scale2{ 2 };
int MCommode::frame3{ 0 };
float MCommode::scale3{ 2 };

struct MBed
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MBed::name{ "Bed" };
const char* MBed::model{ ".\\TestData\\Props\\bed.bmp" };
int MBed::frame{ 0 };
float MBed::scale{ 3 };

struct MCandle
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MCandle::name{ "Candle" };
const char* MCandle::model{ ".\\TestData\\Props\\candle.bmp" };
int MCandle::frame{ 0 };
float MCandle::scale{ 0.5 };

struct MPentagramme
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MPentagramme::name{ "Pentagramme" };
const char* MPentagramme::model{ ".\\TestData\\Props\\pentagramme.bmp" };
int MPentagramme::frame{ 0 };
float MPentagramme::scale{ 3 };

struct MCharlotte
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MCharlotte::name{ "Charlotte Neville" };
const char* MCharlotte::model{ ".\\TestData\\Characters\\charlotte.bmp" };
int MCharlotte::frame{ 1 };
float MCharlotte::scale{ 3 };

struct MFamily
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MFamily::name{ "Family" };
const char* MFamily::model{ ".\\TestData\\Characters\\family.bmp" };
int MFamily::frame{ 1 };
float MFamily::scale{ 3.5 };

struct MCarpet
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MCarpet::name{ "Carpet" };
const char* MCarpet::model{ ".\\TestData\\Props\\carpet-b.bmp" };
int MCarpet::frame{ 1 };
float MCarpet::scale{ 3 };

struct MTriggerScene
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MTriggerScene::name{ "Trigger Scene" };
const char* MTriggerScene::model{ ".\\TestData\\Characters\\charlotte.bmp" };
int MTriggerScene::frame{ 1 };
float MTriggerScene::scale{ 3 };

struct MWardrobe
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MWardrobe::name{ "Wardrobe" };
const char* MWardrobe::model{ ".\\TestData\\Props\\wardrobe.bmp" };
int MWardrobe::frame{ 1 };
float MWardrobe::scale{ 3 };

struct MPage
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MPage::name{ "Page" };
const char* MPage::model{ ".\\TestData\\Props\\page.bmp" };
int MPage::frame{ 1 };
float MPage::scale{ 3 };

struct MWall
{
	static std::string name;
	static const char* model;
	static int frame;
	static float scale;
};

std::string MWall::name{ "Wall" };
const char* MWall::model{ ".\\TestData\\Props\\.bmp" };
int MWall::frame{ 1 };
float MWall::scale{ 3 };


#endif // !MODEL_H
