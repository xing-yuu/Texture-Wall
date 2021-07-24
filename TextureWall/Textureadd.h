#pragma once
#include"stdafx.h"
#include"Setting.h"
class Textureadd
{
public:
	Textureadd();
	~Textureadd();
	
	static double OPattern1(int pointid, int pointnumber, double amplitude);
	static double OPattern2(int pointid, int pointnumber, double amplitude);
	static double OPattern3(int pointid, int pointnumber, double amplitude);
	static double OPattern4(int pointid, int pointnumber, double amplitude);
	static double TPattern1(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static void Function_of_one_ariable(Setting *basicsetting, Model *model);
	static void Function_of_two_ariable(Setting *basicsetting, Model *model);
	
	static void Add_texture(Setting *basicsetting, Model *model);
};

