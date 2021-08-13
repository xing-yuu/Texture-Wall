#include "stdafx.h"
#include "Textureadd.h"
//#include <algorithm>


Textureadd::Textureadd()
{
}


Textureadd::~Textureadd()
{
}

double Textureadd::OPattern1(int pointid, int pointnumber, double amplitude) {
	//第几个点，一共有多少个点，最高点
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
double Textureadd::OPattern6(int pointid, int pointnumber, double amplitude) {//map_leaf
	return (sin(2 * pointid*1.0 / pointnumber * 2 * PI) + cos(2 * pointid*1.0 / pointnumber * 2 * PI)) - (sin(pointid*1.0 / pointnumber * 2 * PI) + cos(pointid*1.0 / pointnumber * 2 * PI));
}
double Textureadd::OPattern7(int pointid, int pointnumber, double amplitude) {//circle
	if (pointid <= (pointnumber *0.5)) {
		return sqrt(0.25*pointnumber*pointnumber - (0.5*pointnumber - pointid)*(0.5*pointnumber - pointid));
	}
	return sqrt(0.25*pointnumber*pointnumber - (0.5*pointnumber - (pointnumber-pointid))*(0.5*pointnumber - (pointnumber - pointid)));
}
double Textureadd::OPattern8(int pointid, int pointnumber, double amplitude) {//circle
	if (pointid <= (pointnumber *0.5)) {
		return 2.0*pointid*amplitude/pointnumber;
	}
	return 2.0*(pointnumber-pointid)*amplitude / pointnumber;
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
double Textureadd::TPattern3(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	double K1 = layernumber * 1.0 / pointnumber;
	double K2 = -layernumber * 1.0 / pointnumber;
	double B = layernumber;
	double Y11 = pointid * K1;
	double Y12 = pointid * K1 - B * 0.5;
	double Y13 = pointid * K1 + B * 0.5;
	double Y21 = pointid * K2 + B;
	double Y22 = pointid * K2 + B * 0.5;
	double Y23 = pointid * K2 + B * 1.5;

	if (pointid <= (pointnumber / 2) && layerid <= (layernumber / 2)) {
		if (pointid <= (pointnumber / 4) && layerid >= Y11 && layerid <= Y22) {
			return 0.5*amplitude * pointid*4.0 / pointnumber;
		}
		if (pointid >= (pointnumber / 4) && layerid >= Y22 && layerid <= Y11) {
			return 0.5*amplitude * ((pointnumber*0.5 - pointid)*4.0 / pointnumber);
		}
		if (layerid <= (layernumber / 4)) {
			return 0.5*amplitude * layerid*4.0 / layernumber;
		}
		return 0.5*amplitude * ((layernumber/2 - layerid)*4.0 / layernumber);
	}
	//向外
	if (pointid <= (pointnumber / 2) && layerid >= (layernumber / 2)) {
		if (pointid <= (pointnumber / 4) && layerid >= Y13 && layerid <= Y21) {
			return -0.5*amplitude * pointid*4.0 / pointnumber;
		}
		if (pointid >= (pointnumber / 4) && layerid <= Y13 && layerid >= Y21) {
			return -0.5*amplitude * ((pointnumber*0.5 - pointid)*4.0 / pointnumber);
		}
		if (layerid <= (3*layernumber / 4)) {
			return -0.5*amplitude * ((layernumber / 2 - (layernumber-layerid))*4.0 / layernumber);
		}
		return -0.5*amplitude * ((layernumber - layerid)*4.0 / layernumber);
	}
	//向内
	if (pointid >= (pointnumber / 2) && layerid <= (layernumber / 2)) {
		if (pointid <= (3 * pointnumber / 4) && layerid >= Y12 && layerid <= Y21) {
			return -0.5*amplitude * (pointid - pointnumber / 2)*4.0 / pointnumber;
		}
		if (pointid >= (3 * pointnumber / 4) && layerid <= Y12 && layerid >= Y21) {
			return -0.5*amplitude * ((pointnumber - pointid)*4.0 / pointnumber);
		}
		if (layerid <= (layernumber / 4)) {
			return -0.5*amplitude * layerid*4.0 / layernumber;
		}
		return -0.5*amplitude * ((layernumber / 2 - layerid)*4.0 / layernumber);
	}
	//向内
	if (pointid >= (pointnumber / 2) && layerid >= (layernumber / 2)) {
		if (pointid <= (3 * pointnumber / 4) && layerid >= Y11 && layerid <= Y23) {
			return 0.5*amplitude * (pointid - pointnumber / 2)*4.0 / pointnumber;
		}
		if (pointid >= (3 * pointnumber / 4) && layerid <= Y11 && layerid >= Y23) {
			return 0.5*amplitude * ((pointnumber - pointid)*4.0 / pointnumber);
		}
		if (layerid <= (3 * layernumber / 4)) {
			return 0.5*amplitude * ((layernumber / 2 - (layernumber - layerid))*4.0 / layernumber);
		}
		return 0.5*amplitude * ((layernumber - layerid)*4.0 / layernumber);
	}
	//向外
}
double Textureadd::TPattern4(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	double k1 = layernumber * 1.0 / pointnumber;
	double k2 = -layernumber * 1.0 / pointnumber;
	double b = layernumber;
	double y11 = pointid * k2 + b * 0.5;
	double y12 = pointid * k2 + b;
	double y21 = pointid * k1 - b * 0.5;
	double y22 = pointid * k1;
	double z = amplitude;
	double y = layernumber;
	double x = pointnumber;

	if (pointid <= (x / 2) && layerid <= y11) {
		return 1.0*(z*y - 2.0*z * layerid) / y - 2.0 * pointid*z / x;
	}
	if (pointid >= (x / 2) && layerid <= y21) {
		return 1.0*(z*y - 2.0*z * layerid) / y - 2.0 * (x - pointid)*z / x;
	}
	if (pointid <= (x / 2) && layerid >= y11 && layerid <= y12) {
		return 2.0*(layerid - k2 * pointid - y *0.5)*z / y;
	}
	if (pointid >= (x / 2) && layerid >= y21 && layerid <= y22) {
		return 2.0*(layerid - k2 * (x - pointid) - y *0.5)*z / y;
	}
	if (pointid <= (x / 2) && layerid >= y12) {
		return 2.0 * z*(0.5 - (layerid - pointid * k2 - y)*1.0 / y);
	}
	return 2.0 * z*(0.5 - (layerid - k2 * (x - pointid) - y)*1.0 / y);
}
double Textureadd::TPattern5(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	double z = amplitude;
	double y = layernumber;
	double x = pointnumber;

	double pi = pointid;
	double li= layerid;
	
	double k0 = y * 1.0 / x;
	double k0_ = -y * 1.0 / x;
	double k1 = x * 1.0 / y;
	double k1_ = -x * 1.0 / y;

	double c1 = y * 0.5 - 0.5 * x * x / y;
	double c2 = 0.5 * x * x / y;

	double y10 = k0 * pi;//correct
	double y11 = k1 * pi;//correct
	double y12 = k1 * pi + 0.5 * y - c2;//correct
	double y13 = k1 * pi + y - 2.0 * c2;//correct
	
	double y20 = k0_ * pi + y;//correct
	double y21 = k1_ * pi + 2.0 * c2;//correct
	double y22 = k1_ * pi + y * 0.5 + c2;//correct
	double y23 = k1_ * pi + y;


	//左下
	if (pi <= (x *0.5) && li <= y11) {
		return 2.0*li*y*z / (x*x);
	}
	if (pi <= (x *0.5) && li >= y11 && li <= y10) {
		return (k0 * pi - li)*z / c1;
	}
	if (pi <= (x *0.5) && li >= y10 && li <= y12) {
		return (li - k0 * pi)*z / c1;
	}
	if (pi <= (x *0.5) && li >= y12 && li <= (y / 2)) {
		return (y * 0.5 - li)*z / c2;
	}
	//else return z;
	//右下
	if (pi >= (x *0.5) && li <= y21) {
		return 2.0*li*y*z / (x*x);
	}
	if (pi >= (x *0.5) && li >= y21 && li <= y20) {
		return (k0 * (x - pi) - li)*z / c1;
	}
	if (pi >= (x *0.5) && li >= y20 && li <= y22) {
		return (li - k0 * (x - pi))*z / c1;
	}
	if (pi >= (x *0.5) && li >= y22 && li <= (y / 2)) {
		return (y * 0.5 - li)*z / c2;
	}
	//左上
	if (pi <= (x *0.5) && li >= (y *0.5) && li <= y22) {
		return (y * 0.5 - (y-li))*z / c2;
	}
	if (pi <= (x *0.5) && li >= y22 && li <= y20) {
		return ((y - li) - k0 * pi)*z / c1;
	}
	if (pi <= (x *0.5) && li >= y20 && li <= y23) {
		return (k0 * pi - (y - li))*z / c1;
	}
	if (pi <= (x *0.5) && li >= y23 && li <= y) {
		return 2.0*(y - li)*y*z / (x*x);
	}
	//右上
	if (pi >= (x *0.5) && li >= (y *0.5) && li <= y12) {
		return (y * 0.5 - (y - li))*z / c2;
	}
	if (pi >= (x *0.5) && li >= y12 && li <= y10) {
		return ((y - li) - k0 * (x - pi))*z / c1;
	}
	if (pi >= (x *0.5) && li >= y10 && li <= y13) {
		return (k0 * (x - pi) - (y - li))*z / c1;
	}
	if (pi >= (x *0.5) && li >= y13 && li <= y) {
		return 2.0*(y - li)*y*z / (x*x);
	}
}
double Textureadd::TPattern6(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	double y = layernumber;
	double x = pointnumber;

	double pi = pointid;
	double li = layerid;

	double k0 = y * 1.0 / x;

	double y1 = -k0 * pi + 0.5*y;
	double y2 = k0 * pi - 0.5*y;
	double y3 = k0 * pi + 0.5*y;
	double y4 = -k0 * pi + 1.5*y;

	if (pi <= (x / 2) && li <= y1) {
		return sqrt((x*(y*0.5 - li) / y)*(x*(y*0.5 - li) / y) - pi * pi)*0.15;
	}
	if (pi <= (x / 2) && li >= y1 && li <= (y / 2)) {
		return sqrt((x*0.5 - x*(y*0.5 - li) / y)*(x*0.5 - x*(y*0.5 - li) / y) - (x*0.5 - pi) * (x*0.5 - pi))*0.15;
	}

	if (pi >= (x / 2) && li <= y2) {
		return sqrt((x*(y*0.5 - li) / y)*(x*(y*0.5 - li) / y) - (x-pi) * (x-pi))*0.15;
	}
	if (pi >= (x / 2) && li >= y2 && li <= (y / 2)) {
		return sqrt((x*0.5 - x * (y*0.5 - li) / y)*(x*0.5 - x * (y*0.5 - li) / y) - (x*0.5 - (x - pi)) * (x*0.5 - (x - pi)))*0.15;
	}
	//return amplitude;
	if (pi <= (x / 2) && li >= (y/2)&&li<=y3) {
		return sqrt((x*0.5 - x * (y*0.5 - (y - li)) / y)*(x*0.5 - x * (y*0.5 - (y - li)) / y) - (x*0.5 - pi) * (x*0.5 - pi))*0.15;
	}
	if (pi <= (x / 2) && li >= y3) {
		return sqrt((x*(y*0.5 - (y - li)) / y)*(x*(y*0.5 - (y - li)) / y) - pi * pi)*0.15;
	}

	if (pi >= (x / 2) && li >= (y/2)&&li<=y4) {
		return sqrt((x*0.5 - x * (y*0.5 - (y - li)) / y)*(x*0.5 - x * (y*0.5 - (y - li)) / y) - (x*0.5 - (x - pi)) * (x*0.5 - (x - pi)))*0.15;
	}
	if (pi >= (x / 2) && li >= y4) {
		
		return sqrt((x*(y*0.5 - (y - li)) / y)*(x*(y*0.5 - (y - li)) / y) - (x - pi) * (x - pi))*0.15;
	}

}
double Textureadd::TPattern7(int pointid, double pointnumber, int layerid, double layernumber, double amplitude) {
	double y = layernumber;
	double x = pointnumber;

	double pid = pointid;
	double li = layerid;

	double k0 = y * 1.0 / x;

	double y1, y2, y3, y4, r;
	/*y1 = -k0 * pi + 0.5*y;
	y2 = k0 * pi - 0.5*y;
	y3 = k0 * pi + 0.5*y;
	y4 = -k0 * pi + 1.5*y;
	if (pi <= (x*0.25) && li <= (y*0.5)) {
		y1 = 0.5*y - sqrt(1 - (pi - 0.25*x)*(pi - 0.25*x) / (x*0.25*x*0.25))*y*0.25;
		//r = x * 0.25*(1 - sqrt(1 - (li - 0.5*y)*(li - 0.5*y) / (y*y*0.25*0.25)));
	}
	else if (pi <= (x*0.5) && pi >= (x*0.25) && li <= (y*0.5)) {
		y1 = sqrt(1 - (pi - 0.25*x)*(pi - 0.25*x) / (x*0.25*x*0.25))*y*0.25;
		//r= x * 0.25*(1 + sqrt(1 - li * li / (y*y*0.25*0.25)));
	}
	else if (pi <= (x*0.25) && li >= (y*0.5)) {
		y3 = 0.5*y + sqrt(1 - (pi - 0.25*x)*(pi - 0.25*x) / (x*0.25*x*0.25))*y*0.25;
	}
	else y3=y- sqrt(1 - (pi - 0.25*x)*(pi - 0.25*x) / (x*0.25*x*0.25))*y*0.25;

	if(pi>=(0.75*x)) y2= 0.5*y - sqrt(1 - ((x-pi) - 0.25*x)*((x-pi) - 0.25*x) / (x*0.25*x*0.25))*y*0.25;
	else y2 = sqrt(1 - ((x-pi) - 0.25*x)*((x-pi) - 0.25*x) / (x*0.25*x*0.25))*y*0.25;

	if(pi>=(0.75*x)) y4= 0.5*y + sqrt(1 - ((x - pi) - 0.25*x)*((x - pi) - 0.25*x) / (x*0.25*x*0.25))*y*0.25;
	else y4= y - sqrt(1 - ((x - pi) - 0.25*x)*((x - pi) - 0.25*x) / (x*0.25*x*0.25))*y*0.25;//*/
	y1 = y * acos((pid - x * 0.25) / (0.25*x)) / (2 * PI);
	y2 = y * acos(((x - pid) - x * 0.25) / (0.25*x)) / (2 * PI);
	y3 = y - y * acos((pid - x * 0.25) / (0.25*x)) / (2 * PI);
	y4 = y - y * acos(((x - pid) - x * 0.25) / (0.25*x)) / (2 * PI);


	if (pid <= (x / 2) && li <= y1) {
		r = x / 4 * (cos(2 * PI*li / y) + 1);
		return sqrt(r*r - pid * pid)*0.3;
	}
	if (pid <= (x / 2) && li >= y1 && li <= (y / 2)) {
		r = x * 0.5 - x / 4 * (cos(2 * PI*li / y) + 1);
		return sqrt(r*r- (x*0.5 - pid) * (x*0.5 - pid))*0.3;
	}

	if (pid >= (x / 2) && li <= y2) {
		r = x / 4 * (cos(2 * PI*li / y) + 1);
		return sqrt(r*r - (x - pid) * (x - pid))*0.3;
	}
	if (pid >= (x / 2) && li >= y2 && li <= (y / 2)) {
		r = x * 0.5 - x / 4 * (cos(2 * PI*li / y) + 1);
		return sqrt(r*r - (x*0.5 - (x - pid)) * (x*0.5 - (x - pid)))*0.3;
	}
	if (pid <= (x / 2) && li >= (y / 2) && li <= y3) {
		r = x * 0.5 - x / 4 * (cos(2 * PI*(y - li) / y) + 1);
		return sqrt(r*r - (x*0.5 - pid) * (x*0.5 - pid))*0.3;
	}
	if (pid <= (x / 2) && li >= y3) {
		r = x / 4 * (cos(2 * PI*(y - li) / y) + 1);
		return sqrt(r*r - pid * pid)*0.3;
	}

	if (pid >= (x / 2) && li >= (y / 2) && li <= y4) {
		r = x * 0.5 - x / 4 * (cos(2 * PI*(y-li) / y) + 1);
		return sqrt(r*r - (x*0.5 - (x - pid)) * (x*0.5 - (x - pid)))*0.3;
	}
	if (pid >= (x / 2) && li >= y4) {
		r = x / 4 * (cos(2 * PI*(y-li) / y) + 1);
		return sqrt(r*r - (x - pid) * (x - pid))*0.3;
	}

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
				if (basicsetting->g_TextureName == "OPattern6") {
					OffsetLength = OPattern6(PointId, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
					//	std::cout << OffsetLength << std::endl;
				}
				if (basicsetting->g_TextureName == "OPattern7") {
					OffsetLength = OPattern7(PointId, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
					//	std::cout << OffsetLength << std::endl;
				}
				if (basicsetting->g_TextureName == "OPattern8") {
					OffsetLength = OPattern8(PointId, basicsetting->g_PointDensity, basicsetting->g_TextureAmplitude);
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
				if (basicsetting->g_TextureName == "TPattern3") {
					OffsetLength = TPattern3(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
					//std::cout << OffsetLength << std::endl;
				}
				if (basicsetting->g_TextureName == "TPattern4") OffsetLength = TPattern4(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "TPattern5") OffsetLength = TPattern5(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "TPattern6") OffsetLength = TPattern6(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
				if (basicsetting->g_TextureName == "TPattern7") OffsetLength = TPattern7(PointId, basicsetting->g_PointDensity, GroupLayerId, GroupLayerNumber, basicsetting->g_TextureAmplitude);
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
	if (basicsetting->g_TextureName == "OPattern6") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "OPattern7") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "OPattern8") {
		Function_of_one_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern1") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern2") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern3") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern4") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern5") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern6") {
		Function_of_two_ariable(basicsetting, model);
	}
	if (basicsetting->g_TextureName == "TPattern7") {
		Function_of_two_ariable(basicsetting, model);
	}
}
