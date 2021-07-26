#include "stdafx.h"
#include "Textureadd.h"


Textureadd::Textureadd()
{
}


Textureadd::~Textureadd()
{
}

double Textureadd::OPattern1(int pointid, int pointnumber, double amplitude) {
	return amplitude*sin(pointid*1.0 / pointnumber * 2 * PI);
}
double Textureadd::OPattern2(int pointid, int pointnumber, double amplitude) {
	return amplitude*sin(pointid*1.0 / pointnumber * PI);
}
double Textureadd::OPattern3(int pointid, int pointnumber, double amplitude) {
	return amplitude*sin(pointid*1.0 / pointnumber * 2 * PI);
}
double Textureadd::OPattern4(int pointid, int pointnumber, double amplitude) {
	return amplitude*sin(pointid*1.0 / pointnumber * 2 * PI);
}
double Textureadd::OPattern5(int pointid, int pointnumber, double amplitude) {
	if (pointid <= pointnumber*1.0 / 8) {
		return 0;
	}
	if (pointid <= pointnumber*3.0 / 8) {
		pointid -= pointnumber*1.0 / 8;
		return amplitude*pointid*1.0 / (pointnumber*1.0 / 4);
	}
	if (pointid <= pointnumber*5.0 / 8) {
		return amplitude;
	}
	if (pointid <= pointnumber*7.0 / 8) {
		pointid -= pointnumber*5.0 / 8;
		return amplitude*(1 - pointid*1.0 / (pointnumber*1.0 / 4));
	}
	return 0;
}
double Textureadd::TPattern1(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	//求出交叉线函数，因为映射，必过（0,0）
	double K1 = layernumber*1.0 / pointnumber;
	double K2 = -layernumber*1.0 / pointnumber;
	double B2 = layernumber;
	double Y1 = pointid*K1;
	double Y2 = pointid*K2 + B2;
	if (pointid <= (pointnumber / 2) && layerid >= Y1&&layerid <= Y2) {
		return amplitude*pointid*2.0 / pointnumber;
	}
	if (pointid >= (pointnumber / 2) && layerid <= Y1&&layerid >= Y2) {
		return amplitude*((pointnumber - pointid)*2.0 / pointnumber);
	}
	if (layerid <= (layernumber / 2)) {
		return amplitude*layerid*2.0 / layernumber;
	}
	return amplitude*((layernumber - layerid)*2.0 / layernumber);
 }

double Textureadd::TPattern2(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	//求出交叉线函数，因为映射，必过（0,0）
	double K1 = layernumber*1.0 / pointnumber;
	double K2 = -layernumber*1.0 / pointnumber;
	double B2 = layernumber;
	double Y1 = pointid*K1;
	double Y2 = pointid*K2 + B2;
	if (pointid <= (pointnumber / 2) && layerid >= Y1&&layerid <= Y2) {
		return -amplitude*pointid*2.0 / pointnumber;
	}
	if (pointid >= (pointnumber / 2) && layerid <= Y1&&layerid >= Y2) {
		return -amplitude*((pointnumber - pointid)*2.0 / pointnumber);
	}
	if (layerid <= (layernumber / 2)) {
		return -amplitude*layerid*2.0 / layernumber;
	}
	return -amplitude*((layernumber - layerid)*2.0 / layernumber);
}


void Textureadd::Function_of_one_ariable(Setting *basicsetting, Model *model) {
	for (int LayerId = 0; LayerId < model->size(); LayerId++) {
		for (int GroupId = 0; GroupId < basicsetting->g_HorizontalCyclesNumber; GroupId++) {
			for (int PointId = 0; PointId < basicsetting->g_PointDensity; PointId++) {
				double OffsetLength = 0;
				if (basicsetting->g_TextureName == "OPattern1") OffsetLength = OPattern1(PointId, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "OPattern2") OffsetLength = OPattern2(PointId, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "OPattern3") OffsetLength = OPattern3((PointId + LayerId) % basicsetting->g_PointDensity, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "OPattern4") OffsetLength = OPattern4(((int)(sin(LayerId*1.0 / model->size() * basicsetting->g_HorizontalCyclesNumber * 2 * PI) * 3) + PointId + basicsetting->g_PointDensity) % basicsetting->g_PointDensity, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "OPattern5") {
					OffsetLength = OPattern5(PointId, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
				//	std::cout << OffsetLength << std::endl;
					
				}
				model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).x += OffsetLength*model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).xn;
				model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).y += OffsetLength*model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).yn;
			}
		}
	}
}
void Textureadd::Function_of_two_ariable(Setting *basicsetting, Model *model) {
	for (int LayerId = 0; LayerId < model->size(); LayerId++) {
		int GroupLayerNumber = model->size()*1.0 / basicsetting->g_VerticalCyclesNumber + 1;
		int GroupLayerId = LayerId % GroupLayerNumber;
		for (int GroupId = 0; GroupId < basicsetting->g_HorizontalCyclesNumber; GroupId++) {//横向分组
			for (int PointId = 0; PointId < basicsetting->g_PointDensity; PointId++) {
				double OffsetLength = 0;
				if (basicsetting->g_TextureName == "TPattern1") OffsetLength = TPattern1(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "TPattern2") OffsetLength = TPattern2(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
			//	if (basicsetting->g_TextureName == "TPattern3") OffsetLength = Pattern3((PointId + LayerId) % basicsetting->g_PointDensity, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
				model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).x += OffsetLength*model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).xn;
				model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).y += OffsetLength*model->at(LayerId).at(GroupId*basicsetting->g_PointDensity + PointId + 1).yn;
			}
		}
	}
}
void Textureadd::Add_texture(Setting *basicsetting, Model *model) {
	if (basicsetting->g_TextureName == "OPattern1") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "OPattern2") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "OPattern3") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "OPattern4") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "OPattern5") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern1") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern2") {
		Function_of_two_ariable(basicsetting, model);
	}
}
