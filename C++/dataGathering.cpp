#include "dataGathering.h"

int samplesPerSecond = 20; // Must also be changed in the arduino code.

void getData(SerialPort dataArduino,std::string fileName) //add teacher mode
{
	float time = 0;
	std::string data = "0";
	std::ofstream outfile(fileName + ".csv");
	outfile << "Time" << "," << "Force" << "\n";
	flushArduinos(dataArduino);
	while (true)
	{
		data = serialRead(dataArduino);
		if (data.find('d') != std::string::npos)
		{
			break;
		}
		outfile << time << ',' << std::stof(data) << std::endl;
		Sleep((1000 / samplesPerSecond)-1);
		time = time+(1.0/samplesPerSecond);
	}
	std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
	return;
}

std::string getValidFileName()
{
	std::string fileName = "";
	std::cout << "Name the file that the data will be saved to." << std::endl;
	std::cin >> fileName;

	while (doesFileExist(fileName))
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "A Test Named " << fileName << " alreadyExists, try another name." << std::endl;
		std::cin >> fileName;
	}
	return fileName;
}

void writeData(std::ofstream outfile, float data) 
{

}

void flushArduinos(SerialPort dataArduino, SerialPort controlArduino) 
{
	std::string temp = "";
	Sleep(100);
	temp = serialRead(controlArduino);
	temp = serialRead(dataArduino);
}

void flushArduinos(SerialPort dataArduino) 
{
	std::string temp = "";
	Sleep(100);
	temp = serialRead(dataArduino);
}