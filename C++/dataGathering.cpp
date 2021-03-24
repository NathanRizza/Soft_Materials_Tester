#include "dataGathering.h"

void getData(SerialPort dataArduino,std::string fileName)
{
	float time = 0;
	float forceValue = 0;
	std::string data = "0";
	std::ofstream outfile(fileName + ".csv"); //"/testData/"+ ?
	outfile << "Time (sec)" << "," << "Force (N)" << "\n";
	flushArduinos(dataArduino);
	while (true)
	{
		data = serialRead(dataArduino);
		if (data.find('d') != std::string::npos)
		{
			break;
		}
		forceValue = std::stof(data);
		forceValue = (forceValue / getConversionFactor());
		outfile << (truncf(time*10)/10) << ',' << forceValue << std::endl;
		Sleep((1000 / getSamplesPerSecond())-1);
		time = time+(1.0/getSamplesPerSecond());
	}
	std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
	return;
}

std::string getValidFileName()
{
	std::string fileName = "";
	std::cout << "Name the file that the data will be saved to. (One word, no spaces)" << std::endl;
	std::cin >> fileName;

	while (doesFileExist(fileName))
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "A Test Named " << fileName << " alreadyExists, try another name." << std::endl;
		std::cin >> fileName;
	}
	return fileName;
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
