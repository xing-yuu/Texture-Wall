// TextureWall.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Setting.h"
#include "Modelgeneration.h"
#include "Gcodegeneration.h"
Setting *basicSetting;
Model *resultModel;
int main()
{
	basicSetting = new Setting;
	basicSetting->Readin_configure("..\\config");
	resultModel = Modelgeneration::Generate_models(basicSetting);
	resultModel = Modelgeneration::Add_back(resultModel, basicSetting);
	Gcodegeneration::Output_Gcode(basicSetting, resultModel);
    return 0;
}

