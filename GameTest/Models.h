#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <string>

struct Table
{
	static std::string name;
	static const char* model;
};

std::string Table::name{ "Table" };
const char* Table::model{ ".\\TestData\\Props\\table.bmp" };

struct Commode
{
	static std::string name;
	static const char* model;
	static const char* model2;
	static const char* model3;

};

std::string Commode::name{ "Commode" };
const char* Commode::model{ ".\\TestData\\Props\\commode.bmp" };
const char* Commode::model2{ ".\\TestData\\Props\\commode2.bmp" };
const char* Commode::model3{ ".\\TestData\\Props\\commode3.bmp" };

struct Bed
{
	static std::string name;
	static const char* model;
	static int frame;
	static int scale;
};

std::string Bed::name{ "Bed" };
const char* Bed::model{ ".\\TestData\\Props\\bed.bmp" };
int Bed::frame{ 0 };
int Bed::scale{ 4 };

struct Cand
{
	static std::string name;
	static const char* model;
};

std::string Cand::name{ "Candle" };
const char* Cand::model{ ".\\TestData\\Props\\candle.bmp" };

struct Pentagramme
{
	static std::string name;
	static const char* model;
};

std::string Pentagramme::name{ "Pentagramme" };
const char* Pentagramme::model{ ".\\TestData\\Props\\pentagramme.bmp" };

struct Charlotte
{
	static std::string name;
	static const char* model;
};

std::string Charlotte::name{ "Charlotte Neville" };
const char* Charlotte::model{ ".\\TestData\\Characters\\charlotte.bmp" };

struct Family
{
	static std::string name;
	static const char* model;
};

std::string Family::name{ "Family" };
const char* Family::model{ ".\\TestData\\Characters\\family.bmp" };


struct Carpet
{
	static std::string name;
	static const char* model;
};

std::string Carpet::name{ "Carpet" };
const char* Carpet::model{ ".\\TestData\\Props\\carpet-b.bmp" };


struct TriggerSc
{
	static std::string name;
	static const char* model;
};

std::string TriggerSc::name{ "Trigger Scene" };
const char* TriggerSc::model{ ".\\TestData\\Characters\\charlotte.bmp" };


struct Wardrobe
{
	static std::string name;
	static const char* model;
};

std::string Wardrobe::name{ "Wardrobe" };
const char* Wardrobe::model{ ".\\TestData\\Props\\wardrobe.bmp" };

#endif // !MODEL_H
