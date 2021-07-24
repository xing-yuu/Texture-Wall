#include "stdafx.h"
#include "Gcodegeneration.h"


Gcodegeneration::Gcodegeneration()
{
}


Gcodegeneration::~Gcodegeneration()
{
}

double Gcodegeneration::Get_Length(point3D v1, point3D v2) 
{ 
	return sqrt((v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y) + (v2.z - v1.z)*(v2.z - v1.z));
}

double Gcodegeneration::Get_Eextrusion(point3D startpoint, point3D endpoint,Setting *basicsetting)
{
	//Line_width * layer_thick / (3.14159*extruderDiameter*extruderDiameter / 4.0);
	return  Get_Length(startpoint, endpoint)*basicsetting->g_ExtrusionRate*(basicsetting->g_LineWidth*basicsetting->g_LayerThickness / (PI*basicsetting->g_ExtruderDiameter*basicsetting->g_ExtruderDiameter / 4.0));
}

void Gcodegeneration::Output_Gcode(Setting *basicsetting, Model *model)
{
	std::ofstream outfile;
	outfile.open(basicsetting->outputFilePath + "/" + basicsetting->g_TextureName + "_" + std::to_string(basicsetting->g_BrickWidth) + "_" + std::to_string(basicsetting->g_HorizontalCyclesNumber) + "_" + std::to_string(basicsetting->g_TextureAmplitude) + ".gcode");

	//确定头文件
	if (basicsetting->g_PrinterID=="CERAMBOT Ultimaker") {
		outfile << "G21; metric values" << std::endl
			<< "G90; absolute positioning" << std::endl
			<< "M82; set extruder to absolute mode" << std::endl
			<< "G28 X0 Y0; move X / Y to min endstops" << std::endl
			<< "G28 Z0; move Z to min endstops" << std::endl
			<< "G1 Z15.0 F1500; move the platform down 15mm" << std::endl
			<< "G92 E0; zero the extruded length" << std::endl
			<< "G1 F200 E3; extrude 3mm of feed stock" << std::endl
			<< "G92 E0; zero the extruded length again" << std::endl
			<< "M302" << std::endl
			<< "G1 F1500" << std::endl;
	}
	if (basicsetting->g_PrinterID == "CERAMBOT ANYCUBIC") {
		outfile << "G21; metric values" << std::endl 
			<< "G90; absolute positioning" << std::endl 
			<< "M82; set extruder to absolute mode" << std::endl 
			<< "G28 X0 Y0; move X / Y to min endstops" << std::endl 
			<< "G28 Z0; move Z to min endstops" << std::endl 
			<< "G1 Z15.0 F1500; move the platform down 15mm" << std::endl 
			<< "G92 E0; zero the extruded length" << std::endl 
			<< "G1 F200 E3; extrude 3mm of feed stock" << std::endl 
			<< "G92 E0; zero the extruded length again" << std::endl 
			<< "M302" << std::endl 
			<< "G1 F1500" << std::endl 
			<< "G0 Y20 F1500" << std::endl 
			<< "M117 Printing..." << std::endl 
			<< "G5" << std::endl;
	}
	if (basicsetting->g_PrinterID == "Eazao Zero") {
		outfile << "G21; metric values" << std::endl 
			<< "G90; absolute positioning" << std::endl 
			<< "M82; set extruder to absolute mode" << std::endl 
			<< "G28 X0 Y0; move X / Y to min endstops" << std::endl 
			<< "G28 Z0; move Z to min endstops" << std::endl 
			<< "G1 Z15.0 F1500; move the platform down 15mm" << std::endl 
			<< "G92 E0; zero the extruded length" << std::endl 
			<< "G1 F200 E3; extrude 3mm of feed stock" << std::endl 
			<< "G92 E0; zero the extruded length again" << std::endl 
			<< "M302" << std::endl 
			<< "G1 F1500" << std::endl 
			<< "M302 S0; always allow extrusion(disable checking)" << std::endl 
			<< "M163 S0 P0.9; Set Mix Factor" << std::endl 
			<< "M163 S1 P0.1; Set Mix Factor" << std::endl 
			<< "M164 S0" << std::endl;

	}
	if (basicsetting->g_PrinterID == "Eazao Mega 5") {
		outfile << "G21; metric values" << std::endl 
			<< "G90; absolute positioning" << std::endl 
			<< "M82; set extruder to absolute mode" << std::endl 
			<< "G28 X0 Y0; move X / Y to min endstops" << std::endl 
			<< "G28 Z0; move Z to min endstops" << std::endl 
			<< "G92 E0; zero the extruded length" << std::endl 
			<< "G1 F200 E3; extrude 3mm of feed stock" << std::endl 
			<< "G92 E0; zero the extruded length again" << std::endl 
			<< "M302" << std::endl 
			<< "G1 F1500" << std::endl;
	}

	int ii = 0;
	float NowUnite = 0;
	point3D LastPoint;
	LastPoint = model->at(0).at(0);
	for (int LayerId = 0; LayerId < model->size(); LayerId++) {
		outfile << ";LAYER:" << LayerId + 1 << std::endl;
		outfile << "G0 X" << model->at(LayerId).at(0).x << " Y" << model->at(LayerId).at(0).y << " Z" << model->at(LayerId).at(0).z << std::endl;
		for (int PointId = 0; PointId < model->at(LayerId).size(); PointId++) {
			NowUnite += Get_Eextrusion(LastPoint, model->at(LayerId).at(PointId), basicsetting);
			outfile << "G1 F" << basicsetting->g_PrinterSpeed << " X" << model->at(LayerId).at(PointId).x << " Y" << model->at(LayerId).at(PointId).y << " Z" << model->at(LayerId).at(PointId).z << " E" << NowUnite << std::endl;
			LastPoint = model->at(LayerId).at(PointId);
		}
	}
	outfile << "G0 Z" << LastPoint.z + 20 << std::endl;

	if (basicsetting->g_PrinterID == "CERAMBOT Ultimaker" || basicsetting->g_PrinterID == "Eazao Zero" || basicsetting->g_PrinterID == "Eazao Mega 5") {
		outfile << "G91; relative positioning" << std::endl 
			<< "G1 F1500 Z + 2; move Z up a bit and retract filament even more" << std::endl 
			<< "G28 X0; move X / Y to min endstops, so the head is out of the way" << std::endl 
			<< "G90" << std::endl;
	}
	if (basicsetting->g_PrinterID == "CERAMBOT ANYCUBIC") {
		outfile << "G91; relative positioning" << std::endl 
			<< "G1 F1500 Z + 2; move Z up a bit and retract filament even more" << std::endl 
			<< "G28 X0; move X / Y to min endstops, so the head is out of the way" << std::endl 
			<< "G90M300 P300 S4000" << std::endl;
	}
}
