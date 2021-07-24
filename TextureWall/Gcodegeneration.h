#pragma once
#include "stdafx.h"
#include "Setting.h"

class Gcodegeneration
{
public:
	Gcodegeneration();
	~Gcodegeneration();
	static double Get_Length(point3D v1, point3D v2);
	static double Get_Eextrusion(point3D startpoint, point3D endpoint, Setting *basicsetting);
	static void Output_Gcode(Setting *basicsetting, Model *model);
};

