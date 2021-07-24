#include "stdafx.h"
#include "Modelgeneration.h"


Modelgeneration::Modelgeneration()
{
}


Modelgeneration::~Modelgeneration()
{
}


Layer *Modelgeneration:: Generate_the_first_layer(point3D StartPoint, point3D EndPoint, int PointsNumber, double PerAngle) {
	Layer *TempFirstLayer = new Layer;
	double ANGLE = 1.0 / PI;
	for (int i = 1; i <= PointsNumber; i++) {
		StartPoint.xn = StartPoint.x / (sqrt(StartPoint.x*StartPoint.x + StartPoint.y*StartPoint.y));
		StartPoint.yn = StartPoint.y / (sqrt(StartPoint.x*StartPoint.x + StartPoint.y*StartPoint.y));
		TempFirstLayer->push_back(StartPoint);
		point3D NextPoint = StartPoint;
		StartPoint.x = NextPoint.x*cos(-PerAngle) - NextPoint.y*sin(-PerAngle);
		StartPoint.y = NextPoint.x*sin(-PerAngle) + NextPoint.y*cos(-PerAngle);//旋转矩阵
	}
	return TempFirstLayer;
}

Model  *Modelgeneration:: Generate_models(Setting *basicsetting) {
	Model *SamplingModel = new Model;//采样模型
	Layer *TheFirstLayer;
	point3D StartCoordinates, EndCoordinates;
	StartCoordinates.x = -(basicsetting->g_BrickWidth / 2);
	StartCoordinates.y = sqrt((basicsetting->g_CircleRadius*basicsetting->g_CircleRadius) - ((basicsetting->g_BrickWidth / 2)*(basicsetting->g_BrickWidth / 2)));
	StartCoordinates.z = basicsetting->g_LayerThickness;
	EndCoordinates.x = -StartCoordinates.x;
	EndCoordinates.y = StartCoordinates.y;
	EndCoordinates.z = basicsetting->g_LayerThickness;
	int PointsNumber = basicsetting->g_PointDensity*basicsetting->g_HorizontalCyclesNumber;
	double PerAngle = acos(StartCoordinates.y / basicsetting->g_CircleRadius) / PointsNumber * 2;
	TheFirstLayer = Generate_the_first_layer(StartCoordinates, EndCoordinates, PointsNumber, PerAngle);
	int LayerNumber = basicsetting->g_BrickHeight / basicsetting->g_LayerThickness;
	for (int i = 1; i < LayerNumber; i++) {
		SamplingModel->push_back(*TheFirstLayer);
		for (int j = 0; j < TheFirstLayer->size(); j++) {
			TheFirstLayer->at(j).z += basicsetting->g_LayerThickness;
		}
	}
	return SamplingModel;
}

Model  *Modelgeneration::Add_back(Model *model, Setting *basicsetting) {

	int SupportNumber = basicsetting->g_SupportsNumber;
	double PerLength = basicsetting->g_BrickWidth / (SupportNumber + 1) - basicsetting->g_LineWidth;
	double PerDeltaZ = basicsetting->g_LayerThickness / SupportNumber;
	for (int LayerId = 0; LayerId < model->size() - 1; LayerId++) {
		point3D LastPoint = model->at(LayerId).at(model->at(LayerId).size() - 1);//取出这一层最后一个点
		LastPoint.y -= basicsetting->g_BrickThickness;
		model->at(LayerId).push_back(LastPoint);//背部第一个点
		for (int SupportId = 1; SupportId <= SupportNumber; SupportId++) {
			LastPoint.x -= PerLength;
			LastPoint.z += PerDeltaZ;
			model->at(LayerId).push_back(LastPoint);
			double DeltaY = sqrt(basicsetting->g_CircleRadius*basicsetting->g_CircleRadius - LastPoint.x*LastPoint.x) - basicsetting->g_TextureAmplitude - basicsetting->g_LineWidth - LastPoint.y;
			LastPoint.y += DeltaY;
			model->at(LayerId).push_back(LastPoint);
			LastPoint.x -= basicsetting->g_LineWidth;
			model->at(LayerId).push_back(LastPoint);
			LastPoint.y -= DeltaY;
			model->at(LayerId).push_back(LastPoint);
		}
		LastPoint = model->at(LayerId + 1).at(0);//下一层第一个点
		LastPoint.y -= basicsetting->g_BrickThickness;
		model->at(LayerId).push_back(LastPoint);
	}
	
	return model;
}