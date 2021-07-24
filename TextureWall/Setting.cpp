#include "stdafx.h"
#include "Setting.h"


void Setting::Readin_configure(std::string CONGFIGPATH) {
	char buffer[256];//读取文件缓存
	std::string inputbuffer;//为了读入文件的便于格式转化

							//错误检查，确保文件打开正确
	std::ifstream in(CONGFIGPATH);
	if (!in.is_open())
	{
		std::cout << "Error opening Configure file!";
		return;
	}
	while (!in.eof())
	{
		in.getline(buffer, 200);
		inputbuffer = buffer;

		//以斜杠开头的是文件中的注释，忽略并读入下一行
		if (inputbuffer[0] == '/') continue;

		else if (inputbuffer == "Texture types")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_TextureName = inputbuffer;
			std::cout << "Texture types: " << g_TextureName << std::endl;
		}
		//水平方向纹理周期的数目
		else if (inputbuffer == "Number of periods of horizontal texture")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_HorizontalCyclesNumber = stod(inputbuffer);
			std::cout << "Number of periods of horizontal texture: " << g_HorizontalCyclesNumber << std::endl;
		}
		else if (inputbuffer == "Number of periods of vertical texture")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_VerticalCyclesNumber = stod(inputbuffer);
			std::cout << "Number of periods of vertical texture: " << g_VerticalCyclesNumber << std::endl;
		}
		else if (inputbuffer == "The density of points")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_PointDensity = stod(inputbuffer);
			std::cout << "The density of points: " << g_PointDensity << std::endl;
		}
		else if (inputbuffer == "Amplitude of texture")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_TextureAmplitude = stod(inputbuffer);
			std::cout << "Amplitude of texture: " << g_TextureAmplitude << std::endl;
		}



		else if (inputbuffer == "The width of the wall tiles")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_BrickWidth = stod(inputbuffer);
			std::cout << "The width of the wall tiles: " << g_BrickWidth << std::endl;
		}
		else if (inputbuffer == "The height of the wall tiles")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_BrickHeight = stod(inputbuffer);
			std::cout << "The height of the wall tiles: " << g_BrickHeight << std::endl;
		}
		else if (inputbuffer == "The thickness of the wall tiles")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_BrickThickness = stod(inputbuffer);
			std::cout << "The thickness of the wall tiles: " << g_BrickThickness << std::endl;
		}
		else if (inputbuffer == "Number of supports of wall tiles")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_SupportsNumber = stod(inputbuffer);
			std::cout << "Number of supports of wall tiles: " << g_SupportsNumber << std::endl;
		}
		else if (inputbuffer == "The radius of the circle")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_CircleRadius = stod(inputbuffer);
			std::cout << "The radius of the circle: " << g_CircleRadius << std::endl;
		}

		else if (inputbuffer == "Line width")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_LineWidth = stod(inputbuffer);
			std::cout << "Line width: " << g_LineWidth << std::endl;
		}
		else if (inputbuffer == "Layer thick")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_LayerThickness = stod(inputbuffer);
			std::cout << "Layer thick: " << g_LayerThickness << std::endl;
		}
		else if (inputbuffer == "Output path")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			outputFilePath = inputbuffer;
			std::cout << "Output path: " << outputFilePath << std::endl;
		}
		else if (inputbuffer == "Printer types")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_PrinterID = inputbuffer;
			std::cout << "Printer types: " << g_PrinterID << std::endl;
		}
		else if (inputbuffer == "Extruder Diameter")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_ExtruderDiameter = stod(inputbuffer);
			std::cout << "Extruder Diameter: " << g_ExtruderDiameter << std::endl;
		}
		else if (inputbuffer == "Printer speed")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_PrinterSpeed = stod(inputbuffer);
			std::cout << "The radius of the circle: " << g_PrinterSpeed << std::endl;
		}

		else if (inputbuffer == "Printer center X")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_CentralX = stod(inputbuffer);
			std::cout << "Printer center X" << g_CentralX << std::endl;
		}
		else if (inputbuffer == "Printer center Y")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_CentralY = stod(inputbuffer);
			std::cout << "Printer center Y: " << g_CentralY << std::endl;
		}
		else if (inputbuffer == "Extrusion rate")
		{
			in.getline(buffer, 100);
			inputbuffer = buffer;
			g_ExtrusionRate = stod(inputbuffer);
			std::cout << "Extrusion rate: " << g_ExtrusionRate << std::endl;
		}
	}
	in.close();
}
