#pragma once
#include "stdafx.h"
#include "Setting.h"

class Gcodegeneration
{
public:
	Gcodegeneration();
	~Gcodegeneration();
	double Get_Length(point3D v1, point3D v2);
	double Get_Eextrusion(point3D startpoint, point3D endpoint, Setting *basicsetting);
	void Output_Gcode(Setting *basicsetting, Model *model);
};

