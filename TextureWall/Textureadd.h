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
	static double OPattern5(int pointid, int pointnumber, double amplitude);
	static double OPattern6(int pointid, int pointnumber, double amplitude);
	static double OPattern7(int pointid, int pointnumber, double amplitude);
	static double OPattern8(int pointid, int pointnumber, double amplitude);
	static double TPattern1(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern2(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern3(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern4(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern5(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern6(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern7(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern8(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern9(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern10(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern11(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern12(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static double TPattern13(int pointid, double pointnumber, int layerid, double layernumber, double amplitude);
	static void Function_of_one_ariable(Setting *basicsetting, Model *model);
	static void Function_of_two_ariable(Setting *basicsetting, Model *model);
	
	static void Add_texture(Setting *basicsetting, Model *model);
};

