// TextureWall.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Setting.h"
#include "Modelgeneration.h"
#include "Gcodegeneration.h"
#include "Textureadd.h"
Setting *basicSetting;
Model *resultModel;
int main()
{
	basicSetting = new Setting;
	basicSetting->Readin_configure("..\\config");
	resultModel = Modelgeneration::Generate_models(basicSetting);
	Textureadd::Add_texture(basicSetting, resultModel);
	resultModel = Modelgeneration::Add_back(resultModel, basicSetting);
	resultModel = Modelgeneration::Move_models(resultModel, basicSetting->g_CentralX, basicSetting->g_CentralY - basicSetting->g_CircleRadius, -1);
	Gcodegeneration::Output_Gcode(basicSetting, resultModel);
    return 0;
}

