#pragma once
#include"stdafx.h"
#include"Setting.h"
class Modelgeneration
{
public:
	Modelgeneration();
	~Modelgeneration();
	static Model *Generate_models(Setting *basicsetting);//生成添加纹理的基础模型
	static Layer *Generate_the_first_layer(point3D StartPoint, point3D EndPoint, int PointsNumber, double PerAngle);//生成第一层的采样点
};

